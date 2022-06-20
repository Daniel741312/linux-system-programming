#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
	struct stat st;
	stat(argv[1], &st);
	if (S_ISDIR(st.st_mode)) {
		printf("%s is dir\n", argv[1]);
	} else if (S_ISREG(st.st_mode)) {
		printf("%s is regular\n", argv[1]);
	} else if (S_ISFIFO(st.st_mode)) {
		printf("%s is fifo\n", argv[1]);
	} else if (S_ISBLK(st.st_mode)) {
		printf("%s is block\n", argv[1]);
	} else {
		printf("others\n");
	}
	return 0;
}