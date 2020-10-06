#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>

// Thread function
void* PrintChild(void* arg){
	int i;
	for(i=0;i<100;i++){
	   printf("Child %d\n",i);
	   usleep(*(int*)arg);
	}
	return NULL;
}
// Main function
void PrintParent(int n){
	int i;
	for(i=0;i<100;i++){
		printf("Parent %d\n",i);
		usleep(n);
	}
}

int main(int argc, char* argv[]){
	pthread_t thread;
	int i, n = atoi(argv[1]);
	printf("Before Execution\n");
	pthread_create(&thread, NULL, PrintChild, (void*) &n);
	PrintParent(n);
	pthread_join(thread,NULL); // Waits for thread to finish before terminating main
	return 0;
}

