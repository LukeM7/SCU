// Luke Manzitto
// Lab9 - Step 5
// Reads from a file entered in command line and copies it to another file. Uses a buffer of a size entered in the command line
// and also takes in the number of threads that will read/write through the file

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *go(void*);

int main(int argc, char *argv[]){
	if(argc <= 3){
		printf("Not all arguments given. Format should be ./step5 <file> <buffer size> <number of threads>\n");
		return -1;
	}
	int i;
	int num_threads = atoi(argv[3]);
	pthread_t threads[num_threads];
	for (i=0;i<num_threads;++i)
		pthread_create(&threads[i],NULL,go,(void*)argv);
	for(i=0;i<num_threads;++i)
		pthread_join(threads[i],NULL);
	return 0;
}

void *go(void *args){
	char **array = (char**)args;
	char buffer[atoi(array[2])];
	FILE *fp, *out;
	fp = fopen(array[1],"rb");
	out = fopen("step5_out.txt","wb");
	while(fread(buffer,sizeof(buffer),1,fp)){
		fwrite(buffer,sizeof(buffer),1,out);
	}
	fclose(fp);
	fclose(out);
	return;
}
