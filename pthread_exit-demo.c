#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

void perr_exit(const char* str) {
	perror(str);
	exit(1);
}

void* tfn(void* arg) {
	long i = (long)arg;
	if (i == 2)
		pthread_exit(NULL);

	printf("I'm %ld thread,pid=%d,tid=%lu\n", i, getpid(), pthread_self());
	sleep(i);
	return NULL;
}

int main(int argc, char* argv[]) {
	long i = 0;

	for (i = 0; i < 5; ++i) {
		pthread_t tid = 0;
		int ret = pthread_create(&tid, NULL, tfn, (void*)i);
		if (ret != 0) {
			perr_exit("pthread_create error");
		}
	}
	sleep(i);
	return 0;
}