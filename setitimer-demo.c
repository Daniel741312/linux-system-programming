#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

void perr_exit(const char* str) {
	perror(str);
	exit(1);
}

void myfunc(int signo) {
	printf("hello, world\n");
	return;
}

int main(int argc, char* argv[]) {
	//为SIGALRM注册回调函数
	signal(SIGALRM, myfunc);
	// 5s后触发，然后每隔1s周期性触发一次
	struct itimerval it = {{1, 0}, {5, 0}};
	struct itimerval oldit;
	int ret = setitimer(ITIMER_REAL, &it, &oldit);
	if (ret < 0) {
		perr_exit("setitimer error");
	}
	while (1)
		;
	return 0;
}
