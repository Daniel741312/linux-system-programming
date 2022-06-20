#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const int BS = 128;

int main(int argc, char* argv[]) {
	int fd = open("/dev/tty", O_RDONLY | O_NONBLOCK);
	if (fd < 0) {
		perror("open /dev/tty error");
		exit(1);
	}
	char buf[BS];
	memset(buf, 0, BS);
	ssize_t n;
	while ((n = read(fd, buf, BS)) < 0) {
		if (errno != EWOULDBLOCK) {
			perror("read /dev/tty error");
			exit(1);
		} else {
			printf("didn't get input, try again\n");
			sleep(1);
		}
	}
	write(STDOUT_FILENO, buf, n);
	close(fd);
	return 0;
}