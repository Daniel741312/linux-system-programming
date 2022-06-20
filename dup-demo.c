#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define CHECK_NEG(x, str) \
	if ((x) < 0) {        \
		perror((str));    \
		exit(1);          \
	}

int main(int argc, char* argv[]) {
	int fd1 = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	CHECK_NEG(fd1, "open error");

	int fd2 = dup(fd1);
	CHECK_NEG(fd2, "dup error");

	printf("fd1 = %d, fd2 = %d\n", fd1, fd2);
	const char* str = "fuckyou";
	write(fd2, str, strlen(str));
	close(fd2);
	return 0;
}