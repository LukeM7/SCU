// Luke Manzitto
// Lab9 - Step 2
// 12/07/2020
// Reads file entered in command line arguement and uses a fixed buffer


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]){
	if(argc <=2){
		printf("Not all arguments given. Format should be ./step2 <file>\n");
		return -1;
	}
	char buffer[1000];
	FILE *fp;
	fp = fopen(argv[1], "rb");
	while (fread(buffer,sizeof(buffer),1,fp)){
	}
	fclose(fp);
	return 0;
}
