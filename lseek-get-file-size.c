#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
	int fd = open(argv[1], O_RDONLY);  //省略了错误处理
	off_t s = lseek(fd, 0, SEEK_END);
	printf("%s size = %ld\n", argv[1], s);
	close(fd);
	return 0;
}