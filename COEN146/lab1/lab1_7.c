//Luke Manzitto
//1/11/2020
//Lab1 - Step 7
//Calculates a series of probabilites related to packet switching

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

double factorial(int);

double factorial(int num){
	int i;
	double factorial = 1;
	for(i=1;i<=num;i++){
		factorial *= (double)i;
	}
	return (double)factorial;
}

int main(int argc, char* argv[]){

	if(argc !=5){
		printf("Bad args: %s <linkBandwidth> <userBandwidth> <tPSuser> <nPSusers>\n", argv[0]);
		return -1;
	}

	int linkBandwidth = atoi(argv[1]);
	int userBandwidth = atoi(argv[2]);
	double tPSuser = atof(argv[3]);
	int nPSusers = atoi(argv[4]);
	
	printf("Link Bandwidth: %d\n",linkBandwidth);
	printf("User Bandwidth: %d\n",userBandwidth);
	printf("tPSuser: %f\n",tPSuser);
	printf("nPSusers: %d\n",nPSusers);	

	double pPSusersBusy = tPSuser;
	printf("a. Probability that a user is busy transmitting: %f\n", pPSusersBusy);

	double pPSusersNotBusy = 1 - pPSusersBusy;
	printf("b. Probability that a (specific) user is not busy: %f\n", pPSusersNotBusy);

	double allNotBusy = pow(1 - pPSusersBusy, nPSusers - 1);
	printf("c. Probability that all of the other specific other users are not busy: %f\n",allNotBusy);

	double oneTransmitterNoOthers = pPSusersBusy * pow(pPSusersNotBusy,nPSusers-1);
	printf("d. Probability that one specific user is transmitting and the remaining users are not: %f\n",oneTransmitterNoOthers);

	double oneTransmitter = nPSusers * (pPSusersBusy * pow(pPSusersNotBusy,nPSusers-1));
	printf("e. Probability that exactly one of the nPSusers is busy: %f\n",oneTransmitter);

	double tenUsers = pow(pPSusersBusy,(double)10) * pow(pPSusersNotBusy,nPSusers-10);
	printf("f. Probability that 10 specific users of nPSusers are transmitting and the others are idle: %g\n",tenUsers);

	double anyTenUsers = (factorial(nPSusers) / (factorial(10) * factorial(nPSusers-10))) * pow(pPSusersBusy,(double)10) * pow(pPSusersNotBusy,(double)(nPSusers-10));
	printf("g. Probability that any 10 users of nPSusers are transmitting and the others are idle: %g\n",anyTenUsers);
	
	int i;
	double result = 0;
	for(i=11;i<=nPSusers;i++){
		result += (factorial(nPSusers) / (factorial(i) * factorial((nPSusers-i)))) * pow(pPSusersBusy,i) * pow(pPSusersNotBusy,(double)(nPSusers-i));
	}
	printf("h. Probability that more than 10 users of nPSusers are transmitting and the others are idle: %g\n",result);
	
	return 0;
}

