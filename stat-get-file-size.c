#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
	struct stat st;
	int ret = stat(argv[1], &st);
	printf("%s size = %ld\n", argv[1], st.st_size);
	return 0;
}