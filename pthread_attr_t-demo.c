#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

void perr_exit(const char* str, int ret) {
	fprintf(stderr, "%s:%s\n", str, strerror(ret));
	pthread_exit(NULL);	 //为了不至于使子线程退出，主线程应调用pthread_exit()而非exit()
}

void* tfn(void* arg) {
	while (1) {
		printf("pid = %d,tid = %lu\n", getpid(), pthread_self());
		sleep(1);
	}
	return NULL;
}

int main(int argc, char* argv[]) {
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

	pthread_t tid;
	pthread_create(&tid, &attr, tfn, NULL);
	int ret = pthread_join(tid, NULL);	//尝试回收，但是会失败，因为前面已经设置了线程分离属性
	pthread_attr_destroy(&attr);
	if (ret != 0) {
		perr_exit("pthread_join error", ret);
	}
	pthread_exit(NULL);	 //为了不至于使子线程退出，主线程应调用pthread_exit()而非exit()
}