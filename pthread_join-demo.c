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

struct thrd {
	int var;
	char str[256];
};

void* tfn(void* arg) {
	struct thrd* pt = (struct thrd*)malloc(sizeof(struct thrd));
	pt->var = 9527;
	strcpy(pt->str, "hello, world");
	return (void*)pt;
}

int main(int argc, char* argv[]) {
	pthread_t tid;
	pthread_create(&tid, NULL, tfn, NULL);
	struct thrd* pt;
	pthread_join(tid, (void**)&pt);
	printf("thread returns pt->var = %d, pt->str = %s\n", pt->var, pt->str);
	free(pt);
	return 0;
}