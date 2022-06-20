#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void perr_exit(const char* str) {
	perror(str);
	exit(1);
}

int main(int argc, char* argv[]) {
	int i = 0;
	for (; i < 5; ++i) {
		pid_t pid = fork();
		if (pid == 0) {
			break;
		}
	}
	if (i < 5) {
		printf("I'm %d child, my pid = %d, my parent pid = %d\n", i, getpid(), getppid());
	} else {
		sleep(3);
		printf("I'm parent, my pid = %d\n", getpid());
	}
	return 0;
}
