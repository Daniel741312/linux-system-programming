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

int main(int argc, char* argv[]) {
	pid_t pid = fork();
	if (pid < 0) {
		perr_exit("fork error");
	} else if (pid == 0) {
		sleep(1);
		kill(getppid(), SIGKILL);
	} else {
		while (1) {
			printf("I'm parent\n");	 //疯狂输出
		}
	}
	return 0;
}
