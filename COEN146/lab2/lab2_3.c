//Luke Manzitto
//1/18/2021
//Lab2 - Step 3
//Copies a file using both API functions and system calls. The time it takes to complete each method is calculated and printed

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

int main(int argc, char* argv[]){
	if(argc != 2){
		printf("Bad args: %s <src.dat>\n",argv[0]);
		return -1;
	}
	clock_t start, end;
	double cpu_time_used;

	start = clock();
	FILE *reader, *writer;
	char buffer[100];
	reader = fopen(argv[1],"r");
	writer = fopen("dest1.dat","w");

	int isReading = 1;
	while(isReading){
		isReading = fread(buffer,sizeof(buffer),1,reader);

		if(feof(reader)){
			fwrite(&buffer,ftell(reader) % sizeof(buffer),1,writer);
			continue;
		}

		fwrite(&buffer,sizeof(buffer),1,writer);
	}
	fclose(reader);
	fclose(writer);
	end = clock();

	cpu_time_used = ((double)(end-start)) / CLOCKS_PER_SEC;

	printf("Step 1 CPU Time: %f\n\n",cpu_time_used);

	start = clock();
	int rd = open(argv[1],O_RDONLY);
	int wd = open("dest2.dat",O_WRONLY | O_TRUNC | O_CREAT,0644);
	ssize_t reading;
	while(reading = read(rd,buffer,sizeof(buffer))){
		write(wd,buffer,reading);
	}
	close(rd);
	close(wd);
	end = clock();

	cpu_time_used = ((double)(end-start)) / CLOCKS_PER_SEC;

	printf("Step 2 CPU Time: %f\n\n",cpu_time_used);

	return 0;
}
