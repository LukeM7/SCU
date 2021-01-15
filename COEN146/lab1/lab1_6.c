//Luke Manzitto
//1/11/2020
//Lab1 - Step 6
//Calculates the number of circuit switched users that can be supported given link and user bandwidths


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int main(int argc, char* argv[]){
	if(argc != 3){
		printf("Bad args. %s <linkBandwidth> <userBandwidth>\n", argv[0]);
		return -1;
	}

	int linkBandwidth = atoi(argv[1]);
	int userBandwidth = atoi(argv[2]);

	printf("Number of circuit-switched users that can be supported: %d\n", linkBandwidth/userBandwidth);

	return 0;
}
