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
	int fd1 = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	int fd2 = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0644);
	int ret = dup2(fd1, fd2);
	printf("ret = %d, fd1 = %d, fd2 = %d\n", ret, fd1, fd2);
	const char* str = "aloha\n";
	write(fd2, str, strlen(str));

	dup2(fd1, STDOUT_FILENO);
	printf("hallo");
	close(fd1);
	close(fd2);
	return 0;
}