#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char* argv[]){
	pid_t pid;
	int i, n = atoi(argv[1]);
	printf("Before fork...\n");
	pid = fork();
	
	if(pid == -1) fprintf(stderr, "Can't fork, Error: %d\n",errno);
	else if(pid == 0){ //Child Process
		execlp("/bin/ls","ls",NULL);
	}
	else{
		wait(NULL);
		printf("Child Complete");
		exit(0);
	}
	return 0;
}
