#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include "set.h"

SET *createDataSet(int maxElts){
	int i;
	SET *sp;
	sp=malloc(sizeof(SET));
	assert(sp!=NULL);
	sp->count=0;
	sp->length=maxElts;
	sp->data=malloc(sizeof(void*)*maxElts);
	assert(sp->data!=NULL);
	return sp;
}

void destroyDataSet(SET *sp){
	assert(sp!=NULL);
	free(sp);
}

int searchAge(SET *sp, int x){
	assert(sp!=NULL);
	int i;
	printf("Searching for student of age %d\n", x);
	for(i=0;i<sp->length;i++){
		if(sp->data[i].age==x){
			return x;
		}
	}
	printf("Age not found\n");
	return -1;
}

void insertion(SET *sp, int x, int y){
	assert(sp!=NULL);
	sp->data[sp->count].age=x;
	sp->data[sp->count].id=y;
	sp->count++;
	return;
}

void deletion(SET *sp, int x){
	assert(sp!=NULL);
	int i;
	for(i=0;i<sp->length;i++){
		if(sp->data[i].age==x){
			printf("ID: %d Age: %d has been deleted\n",sp->data[i].id, sp->data[i].age);
			sp->data[i].age='\0';
			sp->data[i].id='\0';
			sp->count--;
		}
	}
	return;
}
	

int maxAgeGap(SET *sp, int max, int min){
	assert(sp!=NULL);
	int gap = max-min;
	return gap;
}
