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


void* tfn1(void* arg) {
    printf("thread1: returning\n");
    return (void*)111;
}

void* tfn2(void* arg) {
    printf("thread2: exiting\n");
    pthread_exit((void*)222);
}

void* tfn3(void* arg) {
    while(1) {
        printf("thread3: going to die in 3 seconds\n");
        sleep(1);
        //pthread_testcancel(); //手动添加取消点
    }
    return (void*)333;
}

int main() {
    pthread_t tid;
    void* ret;

    pthread_create(&tid, NULL, tfn1, NULL);
    pthread_join(tid, &ret);
    printf("thread1 exit code = %ld\n", (long)ret);

    pthread_create(&tid, NULL, tfn2, NULL);
    pthread_join(tid, &ret);
    printf("thread2 exit code = %ld\n", (long)ret);

    pthread_create(&tid, NULL, tfn3, NULL);
    sleep(3);
    pthread_cancel(tid);
    pthread_join(tid, &ret);
    printf("thread3 exit code = %ld\n", (long)ret);

    return 0;
}