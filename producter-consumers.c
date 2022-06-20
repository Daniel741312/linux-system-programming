#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct Node {
	int val;
	struct Node* next;
};
typedef struct Node Node;
Node* head = NULL;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t has_producted = PTHREAD_COND_INITIALIZER;

void* consumer(void* arg) {
	while (1) {
		pthread_mutex_lock(&lock);
		while (head == NULL) {
			pthread_cond_wait(&has_producted, &lock);
		}
		Node* p = head;
		head = head->next;
		pthread_mutex_unlock(&lock);
		printf("consume %d\n", p->val);
		free(p);
		sleep(rand() % 8);
	}
	return NULL;
}

void* producer(void* arg) {
	while (1) {
		Node* n = (Node*)malloc(sizeof(Node));
		n->val = rand() % 1000;
		printf("produce %d\n", n->val);
		pthread_mutex_lock(&lock);
		n->next = head;
		head = n;
		pthread_mutex_unlock(&lock);
		pthread_cond_signal(&has_producted);
		sleep(rand() % 2);
	}
	return NULL;
}

int main(int argc, char* argv[]) {
	srand(time(NULL));
	pthread_t pid, cid[3];
	pthread_create(&pid, NULL, producer, NULL);
	for (int i = 0; i < 3; ++i) {
		pthread_create(cid + i, NULL, consumer, NULL);
	}

	pthread_join(pid, NULL);
	for (int i = 0; i < 3; ++i) {
		pthread_join(cid[i], NULL);
	}
	return 0;
}