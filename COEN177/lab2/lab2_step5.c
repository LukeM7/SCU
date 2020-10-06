#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

pid_t CreateChildren(){
	pid_t pid;
	pid=fork(); // Creates first child from parent
	if(pid==-1) fprintf(stderr,"Can't fork, error %d\n",errno);

	if(pid){ // if ( parent process )
		pid=fork(); // fork again, creating a second child from the same parent
		if(pid == -1) fprintf(stderr,"Can't fork, error %d\n",errno);
	}
	return pid;
}

int main(int argc, char* argv[]){
	pid_t pid;
	pid=CreateChildren(); // creates two children
	if(pid == -1) fprintf(stderr,"Can't fork, error %d\n", errno);

	else if(pid){
		printf("Parent Process: %d\n",getpid());
		wait();
	}
	else{
		CreateChildren(); // creates another two children from each of the original two child processes, for a total of 7
		printf("\tChild Process: %d Parent Process: %d\n", getpid(), getppid());
	}
	return 0;
}

