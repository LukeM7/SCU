//Luke Manzitto
//1/11/2020
//Lab 1 - Step 2
//Demonstrates using threading to run multiple tasks concurrently

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>

void* go(void* arg){
	int j;
	int n = *(int*)arg;
	for(j=0;j<100;j++){
		printf("Child process %d\n",j);
		usleep(n);
	}
}

int main(int argc, char* argv[]){
	pthread_t thread;
	int i, n = atoi(argv[1]);
	pthread_create(&thread,NULL,go,(void*)&n);
	for(i=0;i<100;i++){
		printf("\t \t \t Parent Process %d \n", i);
		usleep(n);
	}
	pthread_join(thread,NULL);
	return 0;
}
