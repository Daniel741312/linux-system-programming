#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const int BS = 1024;

int main(int argc, char* argv[]) {
	if (argc != 3) {
		printf("format: ./mycp a b\n");
		exit(1);
	}
	int fd1 = open(argv[1], O_RDONLY);
	int fd2 = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd1 == -1 || fd2 == -1) {
		perror("open error");
		exit(1);
	}
	char buf[BS];
	ssize_t s;
	while ((s = read(fd1, buf, BS)) > 0) {
		ssize_t ret = write(fd2, buf, s);
		if (ret != s) {
			perror("write error");
			exit(1);
		}
	}
	if (s < 0) {
		perror("read error");
		exit(1);
	}
	close(fd1);
	close(fd2);
	return 0;
}
