#ifndef skynet_logger_h
#define skynet_logger_h

#define LOG_MAX (4*1024)						// 单条LOG最长4K

void skynet_logger_init(int loglevel, const char *dirname, const char *basename);
void skynet_logger_exit();
void skynet_logger_update();
void skynet_logger_append(const char *src, size_t len);

#endif