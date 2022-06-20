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

int var = 100;

int main(int argc, char* argv[]) {
	pid_t pid = fork();
	if (pid < 0) {
		perr_exit("fork error");
	} else if (pid == 0) {
		printf("beofre write: var = %d,&var = %p, I'm child, my pid = %d, my parent pid = %d\n", var, &var, getpid(), getppid());
		var = 200;
		printf("after write: var = %d, &var = %p, I'm child, my pid = %d, my parent pid = %d\n", var, &var, getpid(), getppid());
	} else {
		printf("before write: var = %d, &var = %p, I'm parent, my pid = %d\n", var, &var, getpid());
		var = 300;
		printf("after write: var = %d, &var = %p, I'm parent, my pid = %d\n", var, &var, getpid());
	}
	return 0;
}
