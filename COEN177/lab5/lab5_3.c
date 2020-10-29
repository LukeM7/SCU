// Luke Manzitto
// 10/26/2020
// Lab5 - step 3
// Uses semaphores to solve the producer-consumer problem

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

#define NTHREADS 10
#define BUFFER_SIZE 10

sem_t empty;
sem_t full;
sem_t mutex;
int buffer[BUFFER_SIZE];
int in = 0, out = 0;

void *Producer(void *arg);
void *Consumer(void *arg);


int main(){
	srand(time(NULL));
	pthread_t threads[NTHREADS];
	sem_init(&empty,0,0); // initialized with a value of 0 for empty
	sem_init(&full,0,BUFFER_SIZE); // initialized with the value of the buffer size for full
	sem_init(&mutex,0,1); // initialized with a value of 1 to represent a mutex
	int i;
	// Runs the producer threads
	for(i=0;i<NTHREADS/2;++i){
			pthread_create(&threads[i],NULL,Producer,(void*)(size_t)i);
			usleep(100);
	}
			// Runs the consumer threads
	for(i=NTHREADS/2;i<NTHREADS;++i){
			pthread_create(&threads[i],NULL,Consumer,(void*)(size_t)i);
			usleep(100);
	}
	// Joins threads back to main
	for(i=0;i<NTHREADS;++i)
		pthread_join(threads[i],NULL);

	sem_destroy(&empty);
	sem_destroy(&full);
	sem_destroy(&mutex);
}

void *Producer(void *arg){
	int item;
	int i = (int)(size_t)arg; // sets i to the arg value. In this case arg is the number of the thread
	do{
		item = rand() % 100;
		//printf("\nItem %d produced by threads %d\n",item,i);
		sem_wait(&empty); // waits until buffer is empty
		sem_wait(&mutex); // "locks" the critical section
		buffer[in] = item;
		in = (in+1) % BUFFER_SIZE;
		printf("\nItem %d produced by thread %d\n",item,i);
		sem_post(&mutex); // "unlocks" the critical section
		sem_post(&full); // signals that the buffer is full
	} while(1);


}

void *Consumer(void *arg){
	int item;
	int i = (int)(size_t)arg; // sets i to number of the thread
	do{
		sem_wait(&full); // waits until buffer is full
		sem_wait(&mutex); // "locks" the critical section
		item = buffer[out];
		out = (out+1) % BUFFER_SIZE;
		sem_post(&mutex); // "unlocks" the critical section
		sem_post(&empty); // signals that the buffer is empty
		printf("\nItem %d consumed by thread %d\n",item,i);
	} while(1);
}
