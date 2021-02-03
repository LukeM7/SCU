//Luke Manzitto
//1/18/2021
//Lab2 - Step 2
//Copies a file given as a CLI argument using system calls

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]){
	if(argc != 2){
		printf("Bad args: %s <src.dat>\n",argv[0]);
		return -1;
	}

	char buffer[17];
	int reader = open(argv[1],O_RDONLY);
	int writer = open("dest2.dat", O_WRONLY | O_TRUNC | O_CREAT,0644);
	ssize_t isReading;
	// while reading bytes, write bytes
	while(isReading = read(reader,buffer,sizeof(buffer))){
		write(writer,buffer,isReading);
	}

	return 0;
}
