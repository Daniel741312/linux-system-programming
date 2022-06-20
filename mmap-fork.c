#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

int var = 100;

void perr_exit(const char* str) {
	perror(str);
	exit(1);
}

int main(int argc, char* argv[]) {
	int fd = open("temp", O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (fd < 0) {
		perr_exit("open error");
	}
	ftruncate(fd, 4);
	int* p = (int*)mmap(NULL, fd, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (p == MAP_FAILED) {
		perr_exit("mmap error");
	}
	close(fd);
	int var = 100;
	pid_t pid = fork();
	if (pid < 0) {
		perr_exit("fork error");
	} else if (pid == 0) {
		printf("child before write: *p = %d, var = %d\n", *p, var);
		*p = 9527;
		var = 200;
		printf("child after write: *p = %d, var = %d\n", *p, var);
	} else {
		sleep(1);
		wait(NULL);
		printf("parent: *p = %d, var = %d\n", *p, var);
		munmap(p, 4);
	}
	return 0;
}