#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
	int ret = link(argv[1], argv[2]);
	if (ret == -1) {
		perror("link error");
		exit(1);
	}

	ret = unlink(argv[1]);
	if (ret == -1) {
		perror("unlink error");
		exit(1);
	}
	return 0;
}
