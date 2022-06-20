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
	int fd = open("ps.log", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0) {
		perr_exit("open error");
	}
	int ret = dup2(fd, STDOUT_FILENO);
	if (ret < 0) {
		perr_exit("dup2 error");
	}
	execlp("ps", "ps", "-aux", NULL);
	perr_exit("execlp error");
	return 0;
}
