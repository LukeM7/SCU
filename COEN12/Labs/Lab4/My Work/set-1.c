#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "list.h"
#define avg_length 20

typedef struct set{
	int count;
	int length;
	LIST **lists;
	int (*compare)();
	unsigned(*hash)();
}SET;

int i,j;

SET *createSet(int maxElts, int(*compare)(), unsigned (*hash)()){ /* O(n) */
	SET *sp;
	sp=malloc(sizeof(SET));
	assert(sp!=NULL);
	sp->count=0;
	sp->length=maxElts/avg_length;
	sp->lists=malloc(sizeof(void*)*sp->length);
	sp->compare=compare;
	sp->hash=hash;
	for(i=0;i<sp->length;i++)
		sp->lists[i]=createList(compare);
	assert(sp->lists!=NULL);
	return sp;
}

void destroySet(SET *sp){ /* O(n) */
	free(sp->lists);
	free(sp);
}

int numElements(SET *sp){
	assert(sp!=NULL);
	return sp->count;
}

void addElement(SET *sp, void *elt){ /* O(n) */
	assert(sp!=NULL && elt!=NULL);
	int place=(*sp->hash)(elt)%sp->length;
	if(findItem(sp->lists[place],elt)==NULL){ /* adds new element to the set if not already found */
		addFirst(sp->lists[place],elt);
		sp->count++;
	}
}

void removeElement(SET *sp, void *elt){ /* O(n) */
	assert(sp!=NULL && elt!=NULL);
	int place=(*sp->hash)(elt)%sp->length;
	if(findItem(sp->lists[place],elt)!=NULL){
		removeItem(sp->lists[place],elt);
		sp->count--;
	}
}

void *findElement(SET *sp, void *elt){ /* O(n^2) */
	assert(sp!=NULL);
	void *data;
	for(i=0;i<sp->length;i++){
		data=findItem(sp->lists[i],elt);
		if(data!=NULL)
			break;
	}
	return data;
}

void *getElements(SET *sp){ /* O(n^3) */
	assert(sp!=NULL);
	int k=0;
	void **array, **copyarray;
	array=malloc(sizeof(void*)*sp->count);
	assert(array!=NULL);
	for(i=0;i<sp->length;i++){
		copyarray=getItems(sp->lists[i]);
		for(j=0;j<numItems(sp->lists[i]);j++){
			array[k]=copyarray[j];
			k++;
		}
	}
	return array;
}

