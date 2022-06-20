#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

void perr_exit(const char* str) {
	perror(str);
	exit(1);
}

int main(int argc, char* argv[]) {
	if (argc < 2) {
		printf("format: ./a.out fifoname\n");
		exit(1);
	}
	int fd = open(argv[1], O_RDONLY);
	if (fd < 0) {
		perr_exit("open error");
	}
	char buf[128];
	while (1) {
		read(fd, buf, sizeof(buf));
		printf("%s", buf);
	}
	close(fd);
	return 0;
}
