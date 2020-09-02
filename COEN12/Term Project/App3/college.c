#include "set.h"

int main(){
	int i;
	srand(time(NULL));
	int temp=0;
	int max = 18;
	int min = 30;
	SET *sp;
	sp = createDataSet(); /* Creates New Data Set */
	printf("Space for 3000 Students has been created\n");
	int firstID = (rand()%2)+1; /* Generates id for first student record */
	int firstAge = (rand()%13)+18; /* Generates age for first student record */
	insertion(sp,firstAge,firstID); /* Inserts first student record into set */
	for(i=0;i<1000;i++){ /* Creates 999 new student records and inserts them into the set */
		int age = rand()%13+18;
		int id = (rand()%2+1+temp);
		temp = id;
		printf("Age: %d ID: %d\n",age,id);
		insertion(sp,age,id); /* Inserts student record into set */
		if(age>max) /* Finds Max Age */
			max=age;
		if(age<min) /* Finds Min Age */
			min=age;
	}
	int stuAge = rand()%13+18; /* Generates Random Student Age */
	int stuID = rand()%2000+1; /* Generates Random Student ID */
	int check = searchID(sp, stuID); /* Checks to see if random student exists in set */
	if(check == -1)
		printf("Student was not found\n");
	else if(check != -1)
		printf("Student: %d ID: %d found in data set\n",stuAge,stuID);
	int randStudentID = (rand() % 2000) + 1; /* Generates a random student ID */
	int locn = searchID(sp, randStudentID); /* Checks to see if random ID exists in set */
	if(locn == -1)
		printf("ID not found in records\n");
	else if(locn != -1)
		deletion(sp,locn); /* If Id exists in set that record is deleted */
	printf("Max Age Gap: %d\n",maxAgeGap(sp,max,min)); /* Prints Max Age Gap */
	destroyDataSet(sp); /* Destroys Set */
}


