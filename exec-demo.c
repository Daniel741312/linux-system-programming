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
	pid_t pid;
	for (; i < 3; ++i) {
		pid = fork();
		if (pid == 0) {
			break;
		}
	}
	if (i == 3) {
		sleep(3);
	} else if (i == 2) {
		//执行系统程序
		execlp("ls", "ls", "-l", "-R", "-h", NULL);
		perr_exit("execlp error");
	} else if (i == 1) {
		//执行自己的程序
		execl("hello", "hello", NULL);
		perr_exit("execl error");
	} else if (i == 0) {
		//以字符串数组的形式传递参数
		execvp("ls", argv);
		perr_exit("execvp error");
	}
	printf("parent finished\n");
	return 0;
}
