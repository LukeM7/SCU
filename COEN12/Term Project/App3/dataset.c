#include "set.h"

SET *createDataSet(){ /* Creates New Data Set */
	int i;
	SET *sp;
	sp=malloc(sizeof(SET)); /* Mallocs memory for set */
	assert(sp!=NULL);
	sp->count=0;
	sp->length=startingLength; /* Sets length to starting length */
	sp->data=malloc(sizeof(void*)*startingLength); /* allocates memory for data */
	assert(sp->data!=NULL);
	return sp;
}

void destroyDataSet(SET *sp){ /* Destroys data set */
	assert(sp!=NULL);
	free(sp);
}

int searchAge(SET *sp, int x){ /* Searches if age exists in records in set */
	assert(sp!=NULL);
	int i;
	printf("Searching for student of age %d\n", x);
	for(i=0;i<sp->length;i++){ /* Runs through set looking if age exists in it */
		if(sp->data[i].age==x){
			return x;
		}
	}
	return -1;
}

int searchID(SET *sp, int y){ /* Searches if given ID is in the set */
	assert(sp!=NULL);
	int i;
	printf("Searching for student ID #%d\n",y);
	for(i=0;i<sp->length;i++){ /* Runs through set looking for the given ID */
		if(sp->data[i].id==y){
			return y;
		}
	}
	return -1;
}

void insertion(SET *sp, int x, int y){ /* Inserts new student record into set */
	assert(sp!=NULL);
	if(sp->count==sp->length){ /* Checks if records have filled data structure */
		sp->data=realloc(sp->data,sizeof(void*)*sp->length*2); /* Dynamically reallocates memory for data if full */
		sp->length=sp->length*2; /* Changes length to fit changed size */
	}
	sp->data[sp->count].age=x;
	sp->data[sp->count].id=y;
	sp->count++;
	return;
}

void deletion(SET *sp, int y){ /* Deletes student record from set */
	assert(sp!=NULL);
	int i;
	for(i=0;i<sp->length;i++){ /* Runs through set looking for records with given ids in set */
		if(sp->data[i].id==y){
			printf("ID: %d Age: %d has been deleted\n",sp->data[i].id, sp->data[i].age);
			sp->data[i].age='\0';
			sp->data[i].id='\0';
			sp->count--;
		}
	}
	return;
}
	

int maxAgeGap(SET *sp, int max, int min){ /* Finds the max age gap */
	assert(sp!=NULL);
	int gap = max-min;
	return gap;
}
