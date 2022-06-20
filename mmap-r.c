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
	int fd = open("temp", O_RDONLY);
	if (fd < 0) {
		perr_exit("open error");
	}
	struct Student* ps = (struct Student*)mmap(NULL, sizeof(struct Student), PROT_READ, MAP_SHARED, fd, 0);
	if (ps == MAP_FAILED) {
		perr_exit("mmap error");
	}
	while (1) {
		printf("stu id = %d, name = %s, age = %d\n", ps->id, ps->name, ps->age);
		sleep(1);
	}
	munmap(ps, sizeof(struct Student));
	close(fd);
	return 0;
}