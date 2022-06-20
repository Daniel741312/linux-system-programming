#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define NUM 5

int arr[NUM];
sem_t empty, full;

void* producer(void* arg) {
	int i = 0;
	while (1) {
		int t = rand() % 1000;
		printf("produce %d\n", t);
		sem_wait(&empty);
		arr[i] = t;
		sem_post(&full);
		i = (i + 1) % NUM;
		sleep(rand() % 3);
	}
	return NULL;
}

void* consumer(void* arg) {
	int i = 0;
	while (1) {
		sem_wait(&full);
		printf("consume %d\n", arr[i]);
		arr[i] = -1;
		sem_post(&empty);
		i = (i + 1) % NUM;
		sleep(rand() % 3);
	}
	return NULL;
}

__attribute__((constructor)) void begin() {
	sem_init(&empty, 0, NUM);
	sem_init(&full, 0, 0);
}

int main() {
	srand(time(NULL));
	pthread_t pid, cid;
	pthread_create(&pid, NULL, producer, NULL);
	pthread_create(&cid, NULL, consumer, NULL);
	pthread_join(pid, NULL);
	pthread_join(cid, NULL);
	return 0;
}

__attribute__((destructor)) void end() {
	sem_destroy(&empty);
	sem_destroy(&full);
}
