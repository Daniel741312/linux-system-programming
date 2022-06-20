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
	printf("tfn:pid=%d,tid=%lu\n", getpid(), pthread_self());
	return NULL;
}

int main(int argc, char* argv[]) {
	pthread_t tid;
	pthread_create(&tid, NULL, tfn, NULL);
	pthread_detach(tid);  //设置线程分离
	sleep(1);
	int ret = pthread_join(tid, NULL);	//这里会出错，不能对一个已经分离出去的子线程回收
	if (ret != 0) {
		printf("pthrad_join error: %s\n", strerror(ret));
		exit(1);
	}
	return 0;
}
