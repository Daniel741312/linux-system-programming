#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void perr_exit(const char* str, int ret) {
	fprintf(stderr, "%s:%s\n", str, strerror(ret));
	exit(1);
}

int cnt = 0;
pthread_rwlock_t rwlock;

void* writer(void* arg) {
	long i = (long)arg;
	while (1) {
		pthread_rwlock_wrlock(&rwlock);
		usleep(10000);
		int t = cnt;
		printf("I'm writer %ld, cnt = %d, ++cnt = %d\n", i, t, ++cnt);
		pthread_rwlock_unlock(&rwlock);
		usleep(100000);
	}
	return NULL;
}

void* reader(void* arg) {
	long i = (long)arg;
	while (1) {
		pthread_rwlock_rdlock(&rwlock);
		printf("I'm reader %ld, cnt = %d\n", i, cnt);
		pthread_rwlock_unlock(&rwlock);
		usleep(20000);
	}
	return NULL;
}

int main() {
	pthread_rwlock_init(&rwlock, NULL);
	pthread_t tid[8];
	long i = 0;
	for (; i < 3; ++i) {
		pthread_create(tid + i, NULL, writer, (void*)i);
	}
	for (; i < 8; ++i) {
		pthread_create(tid + 3 + i, NULL, reader, (void*)i);
	}
	for (i = 0; i < 8; ++i) {
		pthread_join(tid[i], NULL);
	}
	pthread_rwlock_destroy(&rwlock);
}