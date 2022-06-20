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

void func(int signum) {
	printf("catch you %d\n", signum);
}

int main(int argc, char* argv[]) {
	signal(SIGINT, func);
	while (1)
		;
	return 0;
}
