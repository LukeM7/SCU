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
		for(i=1;i<argc;i++){
			write(fds[1],argv[i],strlen(argv[i]));
			write(fds[1],space,1);
		}
	}
	else if(fork()==0){ // reads message from upstream, adds to buffer, then prints the buffer
		printf("Consumer is taking messages from the buffer\n");
		close(fds[1]);
		read(fds[0],&buffer,BUFFER_SIZE);
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

