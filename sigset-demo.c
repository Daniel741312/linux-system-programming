#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void perr_exit(const char* str) {
	perror(str);
	exit(1);
}

void print_sigset(sigset_t* set) {
	for (int i = 1; i < 32; ++i) {
		if (sigismember(set, i)) {
			printf("1");
		} else {
			printf("0");
		}
	}
	printf("\n");
}

int main(int argc, char* argv[]) {
	sigset_t new_sigset, old_sigset, ped_sigset;
	sigemptyset(&new_sigset);
	sigaddset(&new_sigset, SIGINT);	  //屏蔽Ctrl+c
	sigaddset(&new_sigset, SIGQUIT);  //屏蔽Ctrl+'\'
	sigaddset(&new_sigset, SIGBUS);	  //屏蔽SIGBUS
	sigaddset(&new_sigset, SIGKILL);  //屏蔽SIGKILL，但是无效
	sigprocmask(SIG_BLOCK, &new_sigset, &old_sigset);
	while (1) {
		int ret = sigpending(&ped_sigset);	//读取未决信号集
		if (ret == -1) {
			perr_exit("sigpending error");
		}
		print_sigset(&ped_sigset);
		sleep(1);
	}
	return 0;
}