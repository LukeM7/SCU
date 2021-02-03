//Luke Manzitto
//1/18/2021
//Lab2 - Step 1
// Copies one file to a new file using the OS API functions

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
	if(argc != 2){
		printf("Bad args: %s <src.dat>\n",argv[0]);
		return -1;
	}
	FILE* reader,*writer;
	char buffer[17];
	reader = fopen(argv[1],"r");
	writer = fopen("dest1.dat","w");

	int isReading = 1;
	while(isReading){
		isReading = fread(buffer,sizeof(buffer),1,reader);

		//Calculates proper bytes to write at the end of the file -- this is in case of a buffer that is not a multiple of the file size
		if(feof(reader)){
			fwrite(&buffer,ftell(reader) % sizeof(buffer),1,writer);
			continue;
		}

		fwrite(&buffer,sizeof(buffer),1,writer);
	}

	return 0;
}
