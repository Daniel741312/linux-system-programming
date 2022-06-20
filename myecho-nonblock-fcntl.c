#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const int BS = 128;

int main(int argc, char* argv[]) {
	int flag = fcntl(STDIN_FILENO, F_GETFL);
	if (flag < 0) {
		perror("fcntl get error");
	}
	flag |= O_NONBLOCK;
	flag = fcntl(STDIN_FILENO, F_SETFL, flag);
	if (flag < 0) {
		perror("fcntl set error");
	}
	ssize_t n;
	char buf[BS];
	while ((n = read(STDIN_FILENO, buf, BS)) < 0) {
		if (errno != EWOULDBLOCK) {
			perror("read /dev/tty error");
			exit(1);
		} else {
			printf("didn't get input, try again\n");
			sleep(1);
		}
	}
	write(STDOUT_FILENO, buf, n);
	return 0;
}