#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "set.h"

typedef struct set{
	int count;
	int length;
	char **data;
}SET;

int i,place;

static int search(SET *sp, char *elt,bool *found){
	int mid;
	int lo=0;
	int hi=sp->count-1;
	assert(sp!=NULL);
	while(lo<=hi){ /* Finds location of element by cutting the array in half over and over */
		mid=(lo+hi)/2;
		if(strcmp(elt,sp->data[mid])<0)
			hi=mid-1;
		else if(strcmp(elt,sp->data[mid])>0)
			lo=mid+1;
		else{
			*found=true;
			return mid; /* mid is location of element */
		}
	}
	*found=false;
	return lo;
}

SET *createSet(int maxElts){
	SET *sp;
	sp=malloc(sizeof(SET)); /* allocates memory for set */
	assert(sp!=NULL);
	sp->count=0;
	sp->length=maxElts;
	sp->data=malloc(sizeof(char*)*maxElts); /*allocates memory for the array */
	assert(sp->data!=NULL);
	return sp;
}

void destroySet(SET *sp){
	assert(sp!=NULL);
	for(i=0;i<sp->count;i++)
		free(sp->data[i]); /* Frees every element in the array */
	free(sp->data); /* Frees memory taken by the array */
	free(sp);
}

int numElements(SET *sp){
	assert(sp!=NULL);
	return sp->count; /* sp->count keeps track of the number of elements */
}

void addElement(SET *sp, char *elt){
	assert(sp!=NULL);
	bool found=false;
	place=search(sp,elt,&found); /* place is the position of the searched element */
	if(found==false){
		for(i=sp->count;i>place;i--) /* Runs through array and moves elements to keep the list sorted */
			sp->data[i]=sp->data[i-1];
		sp->data[place]=strdup(elt); /* Sets the space in the array to the string */
		sp->count++;
	}
	return;
}

void removeElement(SET *sp, char *elt){
	assert(sp!=NULL);
	bool found=false;
	place=search(sp,elt,&found);
	if(found==true){
		free(sp->data[place]); /* Frees memory held by element */
		if(place!=sp->count-1) /*checks that element does not occupy the last spot */
			for(i=place;i<sp->count;i++)
				sp->data[i]=sp->data[i+1]; /*Move elements to patch the "hole" left by removed element */
		sp->count--;
		return;	
	}	
	return;
}

char *findElement(SET *sp, char *elt){
	assert(sp!=NULL);
	bool found=false;
	place=search(sp,elt,&found); /* looks for position of the desired element */
	if(found==true) 
		return elt;
	return NULL;
}

char **getElements(SET *sp){
	assert(sp!=NULL);
	char **data_2;
	data_2=malloc(sp->count * sizeof(char*)); /* Allocated memory for the new array */
	for(i=0;i<sp->count;i++)
		memcpy(data_2[i],sp->data[i],sizeof(char*)); /* copies each element from the set array into the new one */
	return data_2;
}
