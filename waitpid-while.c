#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

void perr_exit(const char* str) {
	perror(str);
	exit(1);
}

int main(int argc, char* argv[]) {
	int i = 0;
	for (i = 0; i < 5; ++i) {
		pid_t pid = fork();
		if (pid < 0) {
			perr_exit("fork error");
		} else if (pid == 0) {
			break;
		}
	}
	pid_t wpid;
	if (i == 5) {
		while ((wpid = waitpid(-1, NULL, WNOHANG)) != -1) {
			if (wpid == 0) {
				sleep(1);
				continue;
			} else if (wpid > 0) {
				printf("catch child %d\n", wpid);
			}
		}
	} else {
		sleep(1);
		printf("I'm %d child, mypid = %d\n", i, getpid());
	}
	return 0;
}
