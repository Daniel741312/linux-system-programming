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
	int fd1 = open(argv[1], O_RDWR | O_CREAT, 0644);
	int fd2 = fcntl(fd1, F_DUPFD, 0);
	int fd3 = fcntl(fd1, F_DUPFD, 8);
	printf("fd1 = %d, fd2 = %d, fd3 = %d\n", fd1, fd2, fd3);  // fd1 = 3, fd2 = 4, fd3 = 8
	const char* str = "abcdefg";
	write(fd3, str, strlen(str));
	close(fd3);
	return 0;
}