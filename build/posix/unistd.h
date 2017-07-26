#pragma once
#ifndef unistd_h
#define unistd_h

#include <time.h>

#define random rand
#define srandom srand

typedef int ssize_t;
typedef int pid_t;

#ifndef inline
#define inline __inline
#endif

pid_t getpid();
int kill(pid_t pid, int exit_code);

void usleep(size_t us);
void sleep(size_t ms);


/************************************************************************************************/
enum { CLOCK_REALTIME, CLOCK_MONOTONIC, CLOCK_PROCESS_CPUTIME_ID, CLOCK_THREAD_CPUTIME_ID };
int clock_gettime(int what, struct timespec *tp);


/**********************************************************************************************/
typedef int siginfo_t;
enum { SIGPIPE, SIGHUP, SA_RESTART };

struct sigaction {
	void(*sa_handler)(int);
	void(*sa_sigaction)(int, siginfo_t*, void *);
	int sa_flags;
	int sa_mask;
	void(*sa_restorer)(void);
};

void sigfillset(int *flag);
int sigaction(int signo, struct sigaction *act, struct sigaction *oact);


/*
** daemon
*/
int daemon(int a, int b);

enum { LOCK_EX, LOCK_NB };
int flock(int fd, int flag);

/*
** sim pipe
*/
int pipe(int fd[2]);

ssize_t write(int fd, const void *buf, size_t count);
ssize_t read(int fd, void *buf, size_t count);
int close(int fd);

__declspec(dllimport) int __stdcall gethostname(char *buffer, int len);

/*
** util function
*/
char *strsep(char **stringp, const char *delim);

const char *strwsaerror(int err);
const char *strsyserror(int err);
#endif