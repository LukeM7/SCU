#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char* argv[]){
	pid_t pid;
	int i, n = atoi(argv[1]);
	printf("Before forking.\n");
	pid = fork();
	if(pid == -1) fprintf(stderr, "Can't fork, error %d\n", errno);
	if(pid){
		for(i=0;i<100;i++){
			printf("\t\t\tParent Process: %d\n", i);
			usleep(n);
		}
	}
	else{ //Child Process
		for(i=0;i<100;i++){
			printf("Child process %d\n",i);
			usleep(n);
		}
	}
	return 0;
}
