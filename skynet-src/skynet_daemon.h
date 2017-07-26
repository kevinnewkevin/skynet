#ifndef skynet_daemon_h
#define skynet_daemon_h

// for win service
int daemon_install(void);

int daemon_init(const char *pidfile);
int daemon_exit(const char *pidfile);

#endif
