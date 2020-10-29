// Luke Manzitto
// 10/26/2020
// Lab5 - step4
// Solves the producer-consumer problem using mutexes and conditional variables

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

#define NTHREADS 10
#define BUFFER_SIZE 10

pthread_cond_t empty;
pthread_cond_t full; 
pthread_mutex_t mutex;
int buffer[BUFFER_SIZE];
int in = 0, out = 0;
int total_elements = 0;

void *Producer(void *arg);
void *Consumer(void *arg);


int main(){
	srand(time(NULL));
	pthread_t threads[NTHREADS];
	pthread_mutex_init(&mutex,NULL);
	int i;
	// Producer threads
	for(i=0;i<NTHREADS/2;++i)
			pthread_create(&threads[i],NULL,Producer,(void*)(size_t)i);
	
	// Consumer threads
	for(i=NTHREADS/2;i<NTHREADS;++i)
			pthread_create(&threads[i],NULL,Consumer,(void*)(size_t)i);
	
	// Joins threads back to main threads
	for(i=0;i<NTHREADS;++i)
		pthread_join(threads[i],NULL);

	pthread_mutex_destroy(&mutex);
}

void *Producer(void *arg){
	int item;
	int i = (int)(size_t)arg; // sets i to thread index
	do{
		item = rand() % 100;
		pthread_mutex_lock(&mutex); // locks the critical section
		while(total_elements >= BUFFER_SIZE) // condition
			pthread_cond_wait(&empty,&mutex);
		buffer[in] = item;
		in = (in+1) % BUFFER_SIZE;
		total_elements++;
	   	printf("\nItem %d produced by thread %d\n",item,i);	
		pthread_cond_signal(&full); // signals that the buffer is full
		pthread_mutex_unlock(&mutex); // unlocks the critical section
	} while(1);


}

void *Consumer(void *arg){
	int item;
	int i = (int)(size_t)arg; // sets i to thread index
	do{
		pthread_mutex_lock(&mutex); // locks the critical section
		while(total_elements <= 0) // condition
			pthread_cond_wait(&full,&mutex);
		item = buffer[out];
		out = (out+1) % BUFFER_SIZE;
		total_elements--;
		printf("\nItem %d consumed by thread %d\n",item,i);
		pthread_cond_signal(&empty); // signals that the buffer is empty
		pthread_mutex_unlock(&mutex); // unlocks the critical section
	} while(1);
}
