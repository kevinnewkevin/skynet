#include "skynet.h"
#include "skynet_logger.h"
#include "spinlock.h"

#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <assert.h>
#include <pthread.h>
#include <stdbool.h>

#ifdef _MSC_VER
#include <Windows.h>
#else
#include <dirent.h>
#endif // DEBUG

#define ONE_MB	(1024*1024)
#define DEFAULT_ROLL_SIZE (1024*ONE_MB)		// 日志文件达到1G，滚动一个新文件
#define DEFAULT_BASENAME "default"
#define DEFAULT_DIRNAME "."
#define DEFAULT_INTERVAL 5					// 日志同步到磁盘间隔时间


#define LOG_BUFFER_SIZE 4*1024*1024			// 一个LOG缓冲区4M

struct buffer {
	struct buffer* next;
	char data[LOG_BUFFER_SIZE];
	int size;					// 缓冲区已使用字节数
};

struct buffer_list {
	struct buffer* head;
	struct buffer* tail;
};

static void buffer_list_push(struct buffer_list *li, struct buffer *b) {
	if (li->head == NULL) {
		li->head = b;
		li->tail = b;
	} else {
		li->tail->next = b;
		li->tail = b;
	}
	li->tail->next = NULL;
}

static struct buffer * buffer_list_pop(struct buffer_list *li) {
	struct buffer *tmp = NULL;
	if (li->head == NULL) {
		assert(li->tail == NULL);
		return NULL;
	} else if (li->head == li->tail) {
		tmp = li->head;
		li->head = NULL;
		li->tail = NULL;
	} else {
		tmp = li->head;
		li->head = li->head->next;
	}
	return tmp;
}

static bool buffer_list_empty(struct buffer_list *li) {
	return (li->head == li->tail && li->head == NULL);
}

static void buffer_list_clear(struct buffer_list *li) {
	li->head = NULL;
	li->tail = NULL;
}

struct logger {
	FILE* handle;
	int loglevel;
	int rollsize;
	size_t written_bytes;	// 已写入文件的字节数
	int flush_interval;		// 异步日志后端写入文件时间间隔

	int index;
	struct tm tm;
	char basename[32];
	char filename[64];
	char dirname[64];
	struct timespec ts;             // 临时值
	
	struct buffer* curr_buffer;		// 当前缓冲区
	struct buffer_list wbuffers;    // 待写入文件的缓冲区列表
	struct buffer_list sbuffers;
	int running;

	pthread_mutex_t mtx;
	pthread_cond_t cond;
};

static struct logger *TI = NULL;

static const char* get_log_filename(struct logger *inst) {
	memset(inst->filename, 0, 128);
	struct tm tm;
	time_t now = time(NULL);
	localtime_r(&now, &tm);
	if (tm.tm_year == inst->tm.tm_year && tm.tm_yday == inst->tm.tm_yday) {
		inst->index++;
	} else {
		inst->index = 0;
		inst->tm = tm;
	}
	char timebuf[64] = { 0 };
	strftime(timebuf, sizeof(timebuf), ".%Y%m%d", &tm);
	snprintf(inst->filename, 128, "%s%s-%d.log", inst->basename, timebuf, inst->index);
	return inst->filename;
}

static void check_dir(struct logger *inst) {
#ifdef _MSC_VER
	char path[32][32] = { 0 };  // 最多32个
	int offset = 0;
	int s = 0;
	int p = 0;
	int len = strlen(inst->dirname);
	while (p < len) {
		if (inst->dirname[p] == '\\' || inst->dirname[p] == '/') {
			memcpy(path[offset], inst->dirname[s], p - s);
			offset++;
			s = ++p;
		} else {
			p++;
		}
	}
	for (size_t i = 0; i < offset; i++) {
		char tmp[64] = { 0 };
		int tmpoffset = 0;
		for (size_t j = 0; j <= i; j++) {
			int l = strlen(path[j]);
			memcpy(tmp + tmpoffset, path[j], l);
			tmpoffset += l;
#ifdef _MSC_VER
			tmp[tmpoffset] = '\\';
			tmpoffset++;
#else
#endif // _MSC_VER
		}
		tmp[tmpoffset] = '\0';
		tmpoffset--;
#ifdef _MSC_VER
		DWORD attr = GetFileAttributes(inst->dirname);
		if (INVALID_FILE_ATTRIBUTES == attr) {
			CreateDirectory(tmp, NULL);
		} else if (attr & FILE_ATTRIBUTE_DIRECTORY) { // dir
		}
#else
#endif // _MSC_VER
	}
#else
	// 如果不存在，创建文件夹
	DIR* dir;
	dir = opendir(inst.dirname);
	if (dir == NULL) {
		int saved_errno = errno;
		if (saved_errno == ENOENT) {
			if (mkdir(inst.dirname, 0755) == -1) {
				saved_errno = errno;
				fprintf(stderr, "mkdir error: %s\n", strerror(saved_errno));
				exit(EXIT_FAILURE);
			}
		} else {
			fprintf(stderr, "opendir error: %s\n", strerror(saved_errno));
			exit(EXIT_FAILURE);
		}
	} else
		closedir(dir);
#endif // _MSC_VER
}

static void rollfile(struct logger *inst) {
	if (inst->handle == stdin || inst->handle == stdout || inst->handle == stderr)
		return;

	// 结束原来的
	if (inst->handle != NULL && inst->written_bytes > 0) {
		fflush(inst->handle);
		fclose(inst->handle);
	}
	check_dir(inst);
	while (1) {
		char fullpath[128] = { 0 };
		snprintf(fullpath, 128, "%s/%s", inst->dirname, get_log_filename(inst));
		FILE *f = fopen(fullpath, "a+");
		if (f == NULL) {
			int saved_errno = errno;
			fprintf(stderr, "open file error: %s\n", strerror(saved_errno));
			inst->handle = stdout;
			break;
		} else {
			if (inst->written_bytes >= inst->rollsize) {
				// 滚动日志文件
				fclose(inst->handle);
				inst->written_bytes = 0;
				inst->index++;
				continue;
			}

			struct tm tm;
			time_t now = time(NULL);
			localtime_r(&now, &tm);
			inst->tm = tm;
			break;
		}
	}
}

void skynet_logger_init(logger_level loglevel, const char *dirname, const char *basename) {
	struct logger *inst = (struct logger *)skynet_malloc(sizeof(*inst));
	memset(inst, 0, sizeof(*inst));

	inst->handle = stdout;
	inst->loglevel = loglevel;
	inst->rollsize = DEFAULT_ROLL_SIZE;
	inst->flush_interval = DEFAULT_INTERVAL;
	inst->written_bytes = 0;

	inst->index = 0;
	struct tm tm;
	time_t now = time(NULL);
	localtime_r(&now, &tm);
	inst->tm = tm;
	
	inst->curr_buffer = (struct buffer*)skynet_malloc(sizeof(struct buffer));
	buffer_list_clear(&TI->wbuffers);
	buffer_list_clear(&TI->sbuffers);

	if (dirname == NULL)
		strncpy(inst->dirname, DEFAULT_DIRNAME, 64);
	else
		strncpy(inst->dirname, dirname, 64);

	if (basename == NULL)
		strncpy(inst->basename, DEFAULT_BASENAME, 32);
	else
		strncpy(inst->basename, basename, 32);

	pthread_mutex_init(inst->mtx, NULL);
	pthread_cond_init(inst->cond, NULL);

	inst->running = 1;

	rollfile(TI);
	return ;
}

void skynet_logger_exit() {
	TI->running = 0;
	pthread_mutex_destroy(TI->mtx);
	pthread_cond_destroy(TI->cond);
	if (TI->handle)
		fclose(TI->handle);
}

void skynet_logger_update() {
	pthread_mutex_lock(&TI->mtx);
	if (buffer_list_empty(&TI->wbuffers)) {
		clock_gettime(CLOCK_REALTIME, &TI->ts);
		TI->ts.tv_sec += TI->flush_interval;
		pthread_cond_timedwait(&TI->cond, &TI->mtx, &TI->ts);
	}

	struct tm tm;
	time_t now = time(NULL);
	localtime_r(&now, &tm);
	// 新的一天，滚动日志
	if (TI->tm.tm_yday != tm.tm_yday)
		rollfile(TI);
	if (buffer_list_empty(&TI->wbuffers)) {
		pthread_mutex_unlock(&TI->mtx);
	} else {
		struct buffer_list li = TI->wbuffers;
		buffer_list_clear(&TI->wbuffers);
		pthread_mutex_unlock(&TI->mtx);

		struct buffer* node = li.head;
		for (; node != NULL; node = node->next) {
			if (TI->handle) {
#ifdef _MSC_VER
				_fwrite_nolock(node->data, 1, node->size, TI->handle);
#else
				fwrite_unlocked(node->data, 1, node->size, TI->handle);
#endif // _MSC_VER

				
				TI->written_bytes += node->size;
			}
		}

		fflush(TI->handle);
		if (TI->written_bytes > TI->rollsize) {
			TI->index++;
			rollfile(TI);
		}

	}
}

void skynet_logger_append(const char *src, size_t len) {
	pthread_mutex_lock(&TI->mtx);
	if (TI->curr_buffer->size + len < LOG_BUFFER_SIZE) {
		// 当前缓冲区未满，将数据追加到末尾
		memcpy(TI->curr_buffer->data + TI->curr_buffer->size, src, len);
		TI->curr_buffer->size += len;
	} else {
		buffer_list_push(&TI->wbuffers, TI->curr_buffer);

		if (buffer_list_empty(&TI->sbuffers)) {
			struct buffer *n = (struct buffer *)skynet_malloc(sizeof(*n));
			TI->curr_buffer = n;
		} else {
			struct buffer *n = buffer_list_pop(&TI->sbuffers);
			TI->curr_buffer = n;
		}

		memcpy(TI->curr_buffer->data + TI->curr_buffer->size, src, len);
		TI->curr_buffer->size += len;

		pthread_cond_signal(&TI->cond);	// 通知后端开始写入日志
	}
	pthread_mutex_unlock(&TI->mtx);
}