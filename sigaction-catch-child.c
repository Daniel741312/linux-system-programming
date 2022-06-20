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

void catch_child(int signum) {
	pid_t wpid;
	//使用while循环，当多个child同时结束时能够完全回收
	while ((wpid = wait(NULL)) != -1) {
		printf("catch child %d\n", wpid);
	}
}

int main(int argc, char* argv[]) {
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set, SIGCHLD);
	sigprocmask(SIG_BLOCK, &set, NULL);	 //将SIGCHLD信号屏蔽掉
	int i = 0;
	for (; i < 15; ++i) {
		pid_t pid = fork();
		if (pid == 0) {
			break;
		}
	}
	if (i == 15) {
		struct sigaction act, oldact;
		act.sa_handler = catch_child;  //注册信号捕捉函数
		sigemptyset(&(act.sa_mask));
		act.sa_flags = 0;
		sleep(1);  //模拟sigaction调用很长时间
		sigaction(SIGCHLD, &act, &oldact);
		sigprocmask(SIG_UNBLOCK, &set, NULL);  //解除SIGCHLD的屏蔽，开始回收子进程
		printf("I'm parent\n");
		while (1)
			;
	} else {
		printf("I'm %d child\n", i);
	}
	return 0;
}