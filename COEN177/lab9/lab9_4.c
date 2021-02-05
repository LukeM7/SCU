// Luke Manzitto
// Lab9 - Step 4
// 12/07/2020
// Reads from a file entered as command line arguement and uses a buffer of size entered in command line as an arguement. Writes that data to a seperate file.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]){
	if(argc <= 2){
		printf("Not all arguments given. Format should be ./step2 <file> <buffer size>\n");
		return -1;
	}
	char buffer[atoi(argv[2])];
	FILE *fp, *out;
	fp = fopen(argv[1], "rb");
	out = fopen("step4_out.txt","wb");
	while (fread(buffer,sizeof(buffer),1,fp)){
		fwrite(buffer,sizeof(buffer),1,out);
	}
	fclose(fp);
	fclose(out);
	return 0;
}
