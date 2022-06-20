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
	printf("before fork1\n");
	printf("before fork2\n");
	printf("before fork2\n");
	pid_t pid = fork();
	if (pid < 0) {
		perr_exit("fork error");
	} else if (pid == 0) {
		printf("I'm child, my pid = %d, my parent pid = %d\n", getpid(), getppid());
		usleep(10);
	} else {
		printf("I'm parent, my pid = %d\n", getpid());
		pid_t ret = wait(NULL);
		printf("wait %d\n", ret);
	}
	printf("end fork\n");
	return 0;
}
