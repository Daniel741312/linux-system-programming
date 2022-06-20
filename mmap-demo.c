#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void perr_exit(const char* str) {
	perror(str);
	exit(1);
}

int main(int argc, char* argv[]) {
	int fd = open("mmaptext", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0) {
		perr_exit("open error");
	}
	//扩展文件大小到20B
	int ret = ftruncate(fd, 20);
	if (ret < 0) {
		perr_exit("ftruncate error");
	}
	//获取文件大小
	off_t len = lseek(fd, 0, SEEK_END);
	char* p = mmap(NULL, len, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
	if (p == MAP_FAILED) {
		perr_exit("mmap error");
	}
	strcpy(p, "hello, world\n");
	printf("%s", p);
	munmap(p, len);
	return 0;
}