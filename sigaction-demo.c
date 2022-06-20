#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

void perr_exit(const char* str) {
	perror(str);
	exit(1);
}

void catch_signal(int signum) {
	if (signum == SIGINT) {
		printf("catch SIGINT\n");
	} else if (signum == SIGQUIT) {
		printf("catch SIGQUIT\n");
	}
}

int main(int argc, char* argv[]) {
	struct sigaction act, oldact;
	act.sa_handler = catch_signal;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	sigaction(SIGINT, &act, &oldact);
	sigaction(SIGQUIT, &act, &oldact);
	while (1)
		;
	return 0;
}
