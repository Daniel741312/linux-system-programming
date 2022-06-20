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
	pid_t p2;
	for (; i < 5; ++i) {
		pid_t p = fork();
		if (p < 0) {  //错误
			perr_exit("fork error");
		} else if (p > 0) {	 //父进程中
			if (i == 2) {
				p2 = p;
			}
		} else {  //子进程中
			break;
		}
	}
	if (i == 5) {
		// sleep(2);
		pid_t wpid = waitpid(p2, NULL, 0);
		if (wpid < 0) {
			perr_exit("waitpid error");
		} else {
			printf("waitpid a child %d\n", wpid);
		}
	} else {
		sleep(1);
		printf("I'm %d child, mypid = %d\n", i, getpid());
	}

	return 0;
}