#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NTHREADS 10

void* go(void*);
pthread_t threads[NTHREADS];

int main(){
	int i;
	for(i=0;i<NTHREADS;i++)
		pthread_create(&threads[i],NULL,go,&i);
	for(i=0;i<NTHREADS;i++){
		printf("Thread %d returned\n",i);
		pthread_join(threads[i],NULL);
	}
	printf("Main thread done\n");
	return 0;
}

void* go(void* arg){
	printf("hello from thread %d with iteration %d\n",(int)pthread_self(),*(int*)arg);
	return 0;
}
