#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

void perr_exit(const char* str) {
	perror(str);
	exit(1);
}

int main(int argc, char* argv[]) {
	int pfd[2];
	int ret = pipe(pfd);
	if (ret < 0) {
		perr_exit("pipe error");
	}
	const char* str = "hello, world\n";
	pid_t p = fork();
	if (p < 0) {
		perr_exit("fork error");
	} else if (p == 0) {  // child
		close(pfd[0]);
		write(pfd[1], str, strlen(str));
		close(pfd[1]);
	} else {  // parent
		close(pfd[1]);
		char buf[128];
		memset(buf, 0, sizeof(buf));
		read(pfd[0], buf, sizeof(buf));
		printf("%s", buf);
		close(pfd[0]);
	}
	return 0;
}