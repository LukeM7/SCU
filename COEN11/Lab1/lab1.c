#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int division(int divisor,int quotient);
int input;
int main(){
	int dividend,divisor,quotient,i;
	int counter=0;
	int answer;
	srand((int)time(NULL));
	for(i=0;i<10;i++){ /*Goes through all ten division problems */
		divisor=rand()%12+1;
		quotient=rand()%13;
		printf("Dividend: %d  Divisor: %d\n",divisor*quotient,divisor);
		printf("Find the quotient\n");
		scanf("%d",&input);
		answer=division(divisor,quotient);
		if(answer==1){
			printf("Correct!\n");
			counter++;
		}
		else
			printf("Incorrect\n");
	printf("Number Correct: %d\n",counter);
	}
}
int division(int divisor,int quotient){
	if(input==quotient) /*checks user answer to actual answer */
		return 1;
	else
		return 0;
}

