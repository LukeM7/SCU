#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "set.h"
#define FILLED 1
#define EMPTY 0
#define DELETED -1

typedef struct set{
	int count;
	int length;
	void **data;
	char *flag;
	int (*compare)();
	unsigned(*hash)();
}SET;

int i,k,h,place;

static int search(SET *sp, void *elt, bool *found){ /* Expected Runtime: O(1) / Worst-Case Runtime: O(n) */
	int temp=0;
	int save;
	assert(sp!=NULL);
	for(i=0;i<sp->length;i++){
		h=((*sp->hash)(elt)+i)%(sp->length); /* Finds appropriate index through hashing */
		if(sp->flag[h]==FILLED && ((*sp->compare)(sp->data[h],elt))==0){ /* Checks that the element in the filled spot matches the arguement */
			*found=true;
			return h;
		}
		if(sp->flag[h]==DELETED){ /* If a deleted flag is found the location of it is saved in case it needs to be filled */
			if(temp==0){
				save=h;
				temp=1;
			}
		}
		else if(sp->flag[h]==EMPTY){ 
			*found=false;
			if(temp==1) /* Checks if a deleted flag has already been found */
				return save; /* returns index of deleted flag */
			return h;
		}
	}
	*found=false;
	return -1;
}

SET *createSet(int maxElts,int(*compare)(),unsigned(*hash)()){ /* Runtime: O(n) */
	SET *sp;
	sp=malloc(sizeof(SET)); /* allocates memory for set */
	assert(sp!=NULL);
	sp->count=0;
	sp->length=maxElts;
	sp->compare=compare;
	sp->hash=hash; /*points to hash function return */
	sp->flag=malloc(sizeof(char)*maxElts); /* allocated memory for flag array */
	for(i=0;i<maxElts;i++) /* Marks each slot of flag array as empty */
		sp->flag[i]=EMPTY;
	assert(sp->flag!=NULL);
	sp->data=malloc(sizeof(void*)*maxElts); /*allocates memory for the array */
	assert(sp->data!=NULL);
	return sp;
}

void destroySet(SET *sp){ /* Runtime: O(1) */
	assert(sp!=NULL);
	free(sp->flag); /* Frees flag array memory */
	free(sp->data); /* Frees memory taken by the array */
	free(sp); /* Frees set memory */
}

int numElements(SET *sp){ /* Runtime O(1) */
	assert(sp!=NULL);
	return sp->count; /* sp->count keeps track of the number of elements */
}

void addElement(SET *sp, void *elt){ /* Expected Runtime: O(1) / Worst-Case Runtime: O(n) */
	assert(sp!=NULL);
	bool found=false;
	place=search(sp,elt,&found); /* place is the position of the searched element */
	if(found==false){
		sp->data[place]=elt;	/* Fills necessary index with a new element from the arguement */
		sp->flag[place]=FILLED; /* Marks the index of new element as filled */
		sp->count++;
	}
	return;
}

void removeElement(SET *sp, void *elt){ /* Expected Runtime: O(1) / Worst-Case Runtime: O(n) */
	assert(sp!=NULL);
	bool found=false;
	place=search(sp,elt,&found);
	if(found==true){
		sp->flag[place]=DELETED; /* Marks index of desired element as deleted and causes sp->data[place] to be freed */
		sp->count--;
	}
	return;
}

void *findElement(SET *sp, void *elt){ /* Expected Runtime: O(1) / Worst-Case Runtime: O(n) */
	assert(sp!=NULL);
	bool found=false;
	place=search(sp,elt,&found); /* looks for position of the desired element */
	if(found==true) 
		return sp->data[place];
	return NULL;
}

void *getElements(SET *sp){ /* Runtime: O(n) */
	assert(sp!=NULL);
	int check=0;
	char **data_2;
	data_2=malloc(sp->count * sizeof(void*)); /* Allocated memory for the new array */
	for(i=0;i<sp->length;i++){
		if(sp->flag[i]==FILLED){ /* Checks for only filled parts of the original array */
			data_2[check]=sp->data[i]; /* copies over only the remaining memory to new array */
			check++;
		}
	}
	return data_2;
}
