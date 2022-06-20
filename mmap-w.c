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

struct Student {
	int id;
	char name[256];
	int age;
};

void perr_exit(const char* str) {
	perror(str);
	exit(1);
}

int main(int argc, char* argv[]) {
	struct Student stu = {1, "daniel", 22};
	int fd = open("temp", O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (fd < 0) {
		perr_exit("open error");
	}
	ftruncate(fd, sizeof(stu));
	struct Student* ps = (struct Student*)mmap(NULL, sizeof(stu), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (ps == MAP_FAILED) {
		perr_exit("mmap error");
	}
	while (1) {
		memcpy(ps, &stu, sizeof(stu));
		stu.id++;
		sleep(1);
	}
	munmap(ps, sizeof(stu));
	close(fd);
	return 0;
}