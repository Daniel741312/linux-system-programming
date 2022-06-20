#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void perr_exit(const char* str) {
	perror(str);
	exit(1);
}

int main(int argc, char* argv[]) {
	DIR* dirp = opendir(argv[1]);
	struct dirent* sdp;
	while ((sdp = readdir(dirp)) != NULL) {
		if (strcmp(sdp->d_name, ".") == 0 || strcmp(sdp->d_name, "..") == 0) {
			continue;
		} else {
			printf("%s\n", sdp->d_name);
		}
	}
	closedir(dirp);
	return 0;
}