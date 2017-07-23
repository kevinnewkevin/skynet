#ifndef skynet_logger_h
#define skynet_logger_h

#define LOG_MAX (4*1024)						// ����LOG�4K

typedef enum logger_level {
	LOG_DEBUG = 0,
	LOG_INFO = 1,
	LOG_WARNING = 2,
	LOG_ERROR = 3,
	LOG_FATAL = 4
} logger_level;

void skynet_logger_init(logger_level loglevel, const char *dirname, const char *basename);
void skynet_logger_exit();
void skynet_logger_update();
void skynet_logger_append(const char *src, size_t len);

#endif