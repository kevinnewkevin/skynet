#ifndef skynet_xlogger_h
#define skynet_xlogger_h

#define LOG_MAX (4*1024)						// 单条LOG最长4K

typedef enum logger_level {
	LOG_DEBUG = 0,
	LOG_INFO = 1,
	LOG_WARNING = 2,
	LOG_ERROR = 3,
	LOG_FATAL = 4
} logger_level;

void skynet_xlogger_init(logger_level loglevel, const char *dirname, const char *basename);
void skynet_xlogger_exit();
void skynet_xlogger_update();
void skynet_xlogger_append(logger_level level, const char *src, size_t len);

#endif