#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "set.h"

typedef struct set{
	int count;
	int length;
	char **data;
}SET;

int i,place;

static int search(SET *sp, char *elt){
	assert(sp!=NULL);
	for(i=0;i<sp->count;i++){
		if(strcmp(sp->data[i],elt)==0){ /* Looks through array for matching element */
			return i;
		}
	}
	return -1;
}

SET *createSet(int maxElts){
	SET *sp;
	sp=malloc(sizeof(SET)); /* Allocates memory for the set */
	assert(sp!=NULL);
	sp->count=0;
	sp->length=maxElts;
	sp->data=malloc(sizeof(char*)*maxElts); /* Allocates memory for the set array */
	assert(sp->data!=NULL);
	return sp;
}

void destroySet(SET *sp){
	assert(sp!=NULL);
	for(i=0;i<sp->count;i++)
		free(sp->data[i]); /* Frees memory held in the array */
	free(sp->data); /* Free's memory of the array */
	free(sp);
}

int numElements(SET *sp){
	assert(sp!=NULL);
	return sp->count; /* sp->count is the number of elements in the set array */
}

void addElement(SET *sp, char *elt){
	assert(sp!=NULL);
	place=search(sp,elt);
	if(place==-1){
		sp->data[sp->count]=strdup(elt);
		sp->length+=strlen(elt);
		sp->count++;
	}
	return;
}

void removeElement(SET *sp, char *elt){
	assert(sp!=NULL);
	place=search(sp,elt);
	if(place!=-1){
		free(sp->data[place]); /* Frees element memory */
		sp->data[place]=sp->data[sp->count-1]; /* Reorganizes the array */
		sp->count=sp->count-1;
		return;	
	}	
	return;
}

char *findElement(SET *sp, char *elt){
	assert(sp!=NULL);
	place=search(sp,elt); /* Finds location of the element in the array */
	if(place==-1)
		return NULL;
	return sp->data[place];
}

char **getElements(SET *sp){
	assert(sp!=NULL);
	char **data_2;
	data_2=malloc(sp->count * sizeof(char*)); /* Allocates memory for the new array */
	memcpy(data_2,sp->data,sp->count * sizeof(char*)); /* Copies the memory of the set array into the new array */
	return data_2;
}
