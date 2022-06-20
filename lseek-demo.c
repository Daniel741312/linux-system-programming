#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
	int fd = open("./lseek.txt", O_CREAT | O_RDWR, 0644);
	if (fd < 0) {
		perror("open ./lseek.txt error");
		exit(1);
	}
	const char* str = "hello, lseek test\n";
	ssize_t ret = write(fd, str, strlen(str));
	if (ret < 0) {
		perror("write error");
		exit(1);
	}
	//如果这里不将读写指针归零，下面的read读不到任何东西
	lseek(fd, 0, SEEK_SET);
	char c;
	while ((ret = read(fd, &c, 1))) {
		if (ret < 0) {
			perror("read error");
		}
		putchar(c);
	}
	close(fd);
	return 0;
}