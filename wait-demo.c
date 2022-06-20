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
	pid_t p1 = fork();
	if (p1 == 0) {
		printf("I'm child, I'm going to sleep 20s\n");
		sleep(20);
		printf("I'm child, I'm going to die\n");
	} else if (p1 > 0) {
		int status;
		printf("I'm parent\n");
		pid_t p2 = wait(&status);
		if (p2 < 0) {
			perr_exit("wait error");
		}
		if (WIFEXITED(status)) {
			printf("my child exited with %d\n", WEXITSTATUS(status));
		} else if (WIFSIGNALED(status)) {
			printf("my child was killed by %d\n", WTERMSIG(status));
		}
		printf("I'm parent, wait %d == %d finished\n", p1, p2);
	} else {
		perr_exit("fork error");
	}
	return 0;
}
