#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const int BS = 128;

int main() {
	int fd1 = open("./text", O_RDWR | O_CREAT, 0644);
	if (fd1 < 0) {
		perror("open error");
	}
	char buf[BS + 1];
	memset(buf, 0, BS + 1);
	ssize_t s;
	while ((s = read(fd1, buf, BS)) > 0) {
		printf("%s", buf);
		memset(buf, 0, BS + 1);
	}

	const char* str = "fuck the world";
	s = write(fd1, str, strlen(str));
	assert(s == 14);
	close(fd1);
	return 0;
}