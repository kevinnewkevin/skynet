#pragma once
#ifndef unistd_h
#define unistd_h
#include <stdio.h>
#include <fcntl.h>
#include <assert.h>
#include <pthread.h>
#include <stdint.h>
#include <signal.h>


#define random rand
#define srandom srand
#define snprintf _snprintf
typedef int ssize_t;

#ifndef inline
	#define inline __inline
#endif

//typedef long pid_t;
pid_t getpid();
int kill(pid_t pid, int exit_code);

// defined in WinSock2.h
__declspec(dllimport) int __stdcall gethostname(char *buffer, int len);
void usleep(size_t us);
void sleep(size_t ms);

//typedef struct timespec {
//	int tv_sec;
//	int tv_nsec;
//} timespec;

enum { CLOCK_THREAD_CPUTIME_ID, CLOCK_REALTIME, CLOCK_MONOTONIC };
int clock_gettime(int what, struct timespec *ti);

enum { LOCK_EX, LOCK_NB };
int flock(int fd, int flag);


typedef int siginfo_t;
enum { SIGPIPE, SIGHUP, SA_RESTART };

struct sigaction {
	void (*sa_handler)(int);
	void (*sa_sigaction)(int, siginfo_t*, void *);
	int sa_flags;
	int sa_mask;
	void (*sa_restorer)(void);
};

void sigfillset(int *flag);
int sigaction(int signo, struct sigaction *act, struct sigaction *oact);

int pipe(int fd[2]);
int daemon(int a, int b);

char *strsep(char **stringp, const char *delim);

int write(int fd, const void *ptr, size_t sz);
int read(int fd, void *buffer, size_t sz);
int close(int fd);

#endif