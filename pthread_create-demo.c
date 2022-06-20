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
	printf("main:pid=%d,tid=%lu\n", getpid(), pthread_self());

	pthread_t tid = 0;
	int ret = pthread_create(&tid, NULL, tfn, NULL);
	if (ret != 0)
		perr_exit("pthread_create error");

	/*父进程等待1秒,否则父进程一旦退出,地址空间被释放,子线程没机会执行*/
	sleep(1);
	return 0;
}
