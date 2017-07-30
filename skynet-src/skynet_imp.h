#ifndef SKYNET_IMP_H
#define SKYNET_IMP_H

struct skynet_config {
	int thread;
	int harbor;
	int profile;
	int install;
	const char * daemon;
	const char * module_path;
	const char * bootstrap;
	const char * logger;
	const char * logservice;
	const char * logpath;
	const char * logbasename;
};

#define THREAD_WORKER 0
#define THREAD_MAIN 1
#define THREAD_SOCKET 2
#define THREAD_TIMER 3
#define THREAD_MONITOR 4
#define THREAD_XLOGGER 5

void skynet_start(struct skynet_config * config);

#endif
