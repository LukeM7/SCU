/*
Name: Luke Manzitto
Date: 10/12/2020
Title: Lab3 - step 5
Description: the producer-consumer problem demonstrated with pipes
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>

#define BUFFER_SIZE 100

int main(int argc, char* argv[]){
	int i;
	char buffer[BUFFER_SIZE];
	const char* space = " "; // space variable used to separate words in message
	int fds[2];
	pipe(fds);
	if(fork()==0){ // writes message for downstream of pipe
		printf("Producer is adding messages to the buffer\n");
		close(fds[0]);
		// writes message to the buffer
		for(i=1;i<argc;i++){
			strncat(buffer,argv[i],BUFFER_SIZE);
			strncat(buffer,space,BUFFER_SIZE);
		}
		//writes buffer to pipeline
		write(fds[1],buffer,strlen(buffer));:
	}
	else if(fork()==0){ // reads message from upstream, adds to buffer, then prints the buffer
		printf("Consumer is taking messages from the buffer\n");
		close(fds[1]);
		//reads message from pipeline, stores it in buffer
		read(fds[0],&buffer,BUFFER_SIZE);
		// writes buffer to the console
		write(1,&buffer,strlen(buffer));
		printf("\n");
	}
	else{
		close(fds[0]);
		close(fds[1]);
		wait(0);
		wait(0);
	}
	return 0;
}

