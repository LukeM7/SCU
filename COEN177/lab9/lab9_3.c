// Luke Manzitto
// Lab9 - Step 3
// 12/07/2020
// Reads a file given from command line using a buffer whose size is entered in the command line.


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]){
	if(argc <= 2){
		printf("Not all arguments given. Format should be ./step2 <file> <buffer size>\n");
		return -1;
	}
	char buffer[atoi(argv[2])];
	FILE *fp;
	fp = fopen(argv[1], "rb");
	while (fread(buffer,sizeof(buffer),1,fp)){
	}
	fclose(fp);
	return 0;
}
