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
#include <time.h>
#include <unistd.h>

/*创建一把全局锁*/
pthread_mutex_t mutex;

void perr_exit(const char* str, int ret) {
	fprintf(stderr, "%s:%s\n", str, strerror(ret));
	exit(1);
}

void* tfn(void* arg) {
	srand(time(NULL));
	while (1) {
		pthread_mutex_lock(&mutex);
		printf("hello, ");
		sleep(rand() % 4);
		printf("world\n");
		pthread_mutex_unlock(&mutex);
		sleep(rand() % 4);
	}
	return NULL;
}

int main(int argc, char* argv[]) {
	pthread_mutex_init(&mutex, NULL);
	srand(time(NULL));
	pthread_t tid;
	pthread_create(&tid, NULL, tfn, NULL);

	while (1) {
		pthread_mutex_lock(&mutex);
		printf("HELLO, ");
		sleep(rand() % 4);
		printf("WORLD\n");
		pthread_mutex_unlock(&mutex);
		sleep(rand() % 4);
	}

	pthread_mutex_destroy(&mutex);
	pthread_join(tid, NULL);
	return 0;
}
