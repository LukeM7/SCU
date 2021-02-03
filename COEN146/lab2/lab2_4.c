//Luke Manzitto
//1/18/2021
//Lab2 - Step 4
// Copies ten files using a thread for each

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>

void* copy(void* args){
	FILE *reader, *writer;
	char buffer[1000];
	char src_filename[20],dest_filename[20];
	// sprintf will allow for each file to be copied from their assigned thread
	sprintf(src_filename,"tSrc%d.dat",(int)args);
	sprintf(dest_filename,"tDest%d.dat",(int)args);
	reader = fopen(src_filename,"r");
	writer = fopen(dest_filename,"w");

	//Same implementation as step 1 for copying
	int isReading = 1;
	while(isReading){
		isReading = fread(buffer,sizeof(buffer),1,reader);
		
		if(feof(reader)){
			fwrite(&buffer,ftell(reader) % sizeof(buffer),1,writer);
			continue;
		}
		
		fwrite(buffer,sizeof(buffer),1,writer);
	}
}

int main(int argc, char* argv[]){

	pthread_t threads[10];
	int i;
	for(i=0;i<10;i++){
		pthread_create(&threads[i],NULL,copy,(void*)i);
	}

	for(i=0;i<10;i++){
		pthread_join(threads[i],NULL);
	}

	return 1;
}
	
