#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <time.h>
#include "set.h"

#define studentBody 3000

int main(){
	int i;
	srand(time(NULL));
	int temp=0;
	int max = 18;
	int min = 30;
	SET *sp;
	sp = createDataSet(studentBody); /* Creates space for 3000 students */
	printf("Space for 3000 Students has been created\n");
	int firstID = (rand()%2)+1; /* Randomly generates ID of first student */
	int firstAge = (rand()%13)+18; /* Randomly generates age of first student */
	insertion(sp,firstAge,firstID); /* Inserts first student record into array */
	for(i=0;i<1000;i++){ /* Creates 999 student records */
		int age = rand()%13+18;
		int id = (rand()%2+1+temp);
		temp = id;
		printf("Age: %d ID: %d\n",age,id);
		insertion(sp,age,id);
		if(age>max) /* Finds max age */
			max=age;
		if(age<min) /* Finds min age */
			min=age;
	}
	int randAge = rand()%13+18; /* Creates Random Student Age */
	int check = searchAge(sp, randAge);
	if(check == -1) /* Check determines whether student was found in set or not */
		printf("Student not found\n");
	if(check != -1)
		deletion(sp,randAge); /* If found all students of that age are deleted */
	printf("Max Age Gap: %d\n",maxAgeGap(sp,max,min)); /* Prints max age gap */
	destroyDataSet(sp); /* Destroys Set */
}

