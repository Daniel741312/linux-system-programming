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
	int pfd[2];
	int ret = pipe(pfd);
	if (ret < 0) {
		perr_exit("pipe error");
	}
	int i = 0;
	for (; i < 2; ++i) {
		pid_t pid = fork();
		if (pid < 0) {
			perr_exit("fork error");
		} else if (pid == 0) {
			break;
		}
	}

	if (i == 0) {
		close(pfd[0]);
		dup2(pfd[1], STDOUT_FILENO);
		execlp("ls", "ls", NULL);
		perr_exit("execlp error");
	} else if (i == 1) {
		close(pfd[1]);
		dup2(pfd[0], STDIN_FILENO);
		execlp("wc", "wc", "-l", NULL);
		perr_exit("execlp error");
	} else {  // parent
		close(pfd[0]), close(pfd[1]);
		wait(NULL), wait(NULL);
	}
	return 0;
}
