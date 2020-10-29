// Luke Manzitto
// 10/26/2020
// Lab5 - step1
// This program runs given code to demonstrate the use of semaphores when accessing a critical section.

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>

#define NTHREADS 10
pthread_t threads[NTHREADS];
sem_t *mutex;

void *go(void *arg){
	sem_wait(mutex);
	printf("Thread %d Entered Critical Section... \n", (int)arg);
	sleep(1);
	sem_post(mutex);
	return NULL;
}

int main(){
	sem_unlink("mutex2");
	mutex = sem_open("mutex2",O_CREAT,0644,1);
	static int i;
	for(i=0;i<NTHREADS;i++){
		pthread_create(&threads[i], NULL, go, (void*)(size_t)i);
		//usleep(10);
	}
	for(i=0;i<NTHREADS;i++){
		pthread_join(threads[i],NULL);
		printf("\t\t\tThread %d returned \n",i);
		//usleep(10);
	}
	printf("Main thread done\n");
	sem_unlink("mutex2");
	return 0;
}
