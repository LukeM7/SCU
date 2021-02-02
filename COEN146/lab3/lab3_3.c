//Luke Manzitto
//01/25/2021
//Lab 3 - Step 3
// Calculates the RTT time elapsed for several scenarios

#include <stdio.h>

int main(){
	// these variables are measured in ms
	int RTT0 = 3, RTT1 = 20, RTT2 = 26, RTTHTTP = 47;

	// Part A
	printf("Part A - Time Elapsed: \n");
	int A = RTT0 + RTT1 + RTT2 + (2*RTTHTTP);
	printf("%dms\n\n",A);

	// Part B
	printf("Part B - Time Elapsed: \n");
	int B = RTT0 + RTT1 + RTT2 + (2*RTTHTTP) + (2*6*RTTHTTP);
	printf("%dms\n\n",B);

	//Part C
	printf("Part C - Time Elapsed: \n");

	printf("\nNon-Persistent Connections: \n");
	//Non-Persistent connections
	int response_times[6]; // Each index corresponds to how many TCP connections there are in parallel
	response_times[0] = RTT0 + RTT1 + RTT2 + (2*RTTHTTP) + (2*6*RTTHTTP);
	response_times[1] = RTT0 + RTT1 + RTT2 + (8*RTTHTTP);
	response_times[2] = RTT0 + RTT1 + RTT2 + (6*RTTHTTP);
	response_times[3] = RTT0 + RTT1 + RTT2 + (6*RTTHTTP);
	response_times[4] = RTT0 + RTT1 + RTT2 + (6*RTTHTTP);
	response_times[5] = RTT0 + RTT1 + RTT2 + (4*RTTHTTP);
	
	int i;
	for(i=0;i<6;i++) printf("%d TCP Parallel Connections: %dms\n",i+1,response_times[i]);
	
	printf("\nPersistent Connections:\n");
	//Persistent Connections
	response_times[0] = RTT0 + RTT1 + RTT2 + (8*RTTHTTP);
	response_times[1] = RTT0 + RTT1 + RTT2 + (5*RTTHTTP);
	response_times[2] = RTT0 + RTT1 + RTT2 + (4*RTTHTTP);
	response_times[3] = RTT0 + RTT1 + RTT2 + (4*RTTHTTP);
	response_times[4] = RTT0 + RTT1 + RTT2 + (4*RTTHTTP);
	response_times[5] = RTT0 + RTT1 + RTT2 + (3*RTTHTTP);

	for(i=0;i<6;i++) printf("%d TCP Parallel Connections: %dms\n",i+1,response_times[i]);

	return 0;
}	
