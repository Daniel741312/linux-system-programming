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

void perr_exit(const char* str, int ret) {
	fprintf(stderr, "%s:%s\n", str, strerror(ret));
	exit(1);
}

void* tfn(void* arg) {
	while (1) {
		printf("pid = %d,tid = %lu\n", getpid(), pthread_self());
		sleep(1);
	}
	return NULL;
}

int main(int argc, char* argv[]) {
	pthread_t tid;
	pthread_create(&tid, NULL, tfn, NULL);
	//等待5s后杀死该线程
	sleep(5);
	int ret = pthread_cancel(tid);
	if (ret != 0) {
		perr_exit("pthread_cancel error", ret);
	}
	return 0;
}
