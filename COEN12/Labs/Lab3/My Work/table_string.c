#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "set.h"
#define FILLED 1
#define EMPTY 0
#define DELETED -1

unsigned strhash(char *elt){ /* Hash function */
	unsigned hash=0;
	while(*elt!='\0')
		hash=31 * hash + *elt ++;
	return hash;
}

typedef struct set{
	int count;
	int length;
	char **data;
	char *flag;
}SET;

int i,k,h,place;

static int search(SET *sp, char *elt, bool *found){
	int temp=0;
	int save;
	k=strhash(elt)%sp->length; /* Creates key for hash function */
	assert(sp!=NULL);
	for(i=0;i<sp->length;i++){
		h=(k+i)%sp->length; /* Finds appropriate index for hashing */
		if(sp->flag[h]==FILLED && strcmp(sp->data[h],elt)==0){ /* Checks that filled spot's element is the same as the one in the arguement */
				*found=true;
				return h;
		}
		if(sp->flag[h]==DELETED){
			if(temp==0){
				save=h; /* Saves index in case element not found if deleted slot exists */
				temp=1;
			}
		}
		else if(sp->flag[h]==EMPTY){ 
			if(temp==1){ /* Checks no deleted slot exists */
				*found=false;
				return save;
			}
			return h;
		}
	}
	return -1;
}

SET *createSet(int maxElts){ /* Runtime: O(n) */
	SET *sp;
	sp=malloc(sizeof(SET)); /* allocates memory for set */
	assert(sp!=NULL);
	sp->count=0;
	sp->length=maxElts;
	sp->flag=malloc(sizeof(char)*maxElts); /* Allocated memory to flag array */
	for(i=0;i<maxElts;i++)
		sp->flag[i]=EMPTY; /* Marks every element of array as filled */
	assert(sp->flag!=NULL);
	sp->data=malloc(sizeof(char*)*maxElts); /*allocates memory for the array */
	assert(sp->data!=NULL);
	return sp;
}

void destroySet(SET *sp){ /* Runtime: O(n) */
	assert(sp!=NULL);
	for(i=0;i<sp->length;i++){
		if(sp->flag[i]==FILLED)
			free(sp->data[i]);	/* Frees every element in the array */
	}
	free(sp->flag); /* Frees flag array memory */
	free(sp->data); /* Frees memory taken by the array */
	free(sp);
}

int numElements(SET *sp){ /* Runtime: O(1) */
	assert(sp!=NULL);
	return sp->count; /* sp->count keeps track of the number of elements */
}

void addElement(SET *sp, char *elt){ /* Expected Runtime: O(1) / Worst-Case Runtime: O(n) */
	assert(sp!=NULL);
	bool found=false;
	place=search(sp,elt,&found); /* place is the position of the searched element */
	if(found==false){
		sp->data[place]=strdup(elt);	/* Puts new element in the array */
		sp->flag[place]=FILLED; /* Marks index as filled */
		sp->count++;
	}
}

void removeElement(SET *sp, char *elt){ /* Expected Runtime: O(1) / Worst-Case Runtime: O(n) */
	assert(sp!=NULL);
	bool found=false;
	place=search(sp,elt,&found); /* Looks for position of the desired element */
	if(found==true){
		free(sp->data[place]); /* Frees memory held by element */
		sp->flag[place]=DELETED; /* Marks index as deleted */
		sp->count--;
	}	
}

char *findElement(SET *sp, char *elt){ /* Expected Runtime: O(1) / Worst-Case Runtime: O(n) */
	assert(sp!=NULL);
	bool found=false;
	place=search(sp,elt,&found); /* Looks for position of the desired element */
	if(found==true) 
		return elt;
	return NULL;
}

char **getElements(SET *sp){ /* Runtime: O(n) */
	assert(sp!=NULL);
	int check=0;
	char **data_2;
	data_2=malloc(sp->count * sizeof(char*)); /* Allocated memory for the new array */
	for(i=0;i<sp->length;i++){
		if(sp->flag[i]==FILLED){ /* Checks if index is filled */
			data_2[check]=strdup(sp->data[i]); /* Copies only filled memory into new array */
			check++;
		}
	}
	return data_2;
}
