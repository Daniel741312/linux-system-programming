#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const int BS = 1024;

int main(int argc, char* argv[]) {
	char buf[BS];
	int ret = read(STDIN_FILENO, buf, BS);
	if (ret < 0) {
		perror("read error");
		exit(1);
	}
	ret = write(STDOUT_FILENO, buf, ret);
	if (ret < 0) {
		perror("read error");
		exit(1);
	}
	return 0;
}
