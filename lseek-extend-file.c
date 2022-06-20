#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
	int fd = open(argv[1], O_RDWR);
	int ret = lseek(fd, 198, SEEK_END);
	write(fd, "\0", 1);
	close(fd);
	return 0;
}
