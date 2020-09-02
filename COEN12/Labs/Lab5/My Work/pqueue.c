#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "pqueue.h"
#define starting_length 10
#define p(x) (((x)-1)/2)
#define l(x) (((x)*2)+1)
#define r(x) (((x)*2)+2)

typedef struct pqueue{ 
	int count;
	int length;
	void **data;
	int(*compare)();
}PQ;

PQ *createQueue(int(*compare)()){ /* Runtime: O(1). Creates priority queue */
	PQ *pq;
	pq=malloc(sizeof(PQ));
	assert(pq!=NULL);
	pq->count=0;
	pq->length=starting_length;
	pq->compare=compare;
	assert(compare!=NULL);
	pq->data=malloc(sizeof(void*)*starting_length);
	return pq;
}

void destroyQueue(PQ *pq){ /* Runtime: O(1). Destroys priority queue */
	assert(pq!=NULL);
	int i;
	for(i=0;i<pq->count;i++)
		free(pq->data[i]);
	free(pq->data);
	free(pq);
}

int numEntries(PQ *pq){ /* Runtime: O(1). Shows number of nodes in priority queue */
	assert(pq!=NULL);
	return pq->count;
}

void addEntry(PQ *pq, void *entry){ /* Runtime: O(log n). Adds a node to the priority queue */
	assert(pq!=NULL && entry!=NULL);
	if(pq->count==pq->length){ /* Dynamically reallocates memory to double the size */
		pq->data=realloc(pq->data,sizeof(void*)*pq->length*2);
		pq->length=pq->length*2;
	}
	pq->data[pq->count]=entry;
	int index=pq->count;
	while(pq->compare(pq->data[index],pq->data[p(index)])<0){
		void *temp=pq->data[p(index)];
		pq->data[p(index)]=pq->data[index];
		pq->data[index]=temp;
	}
	pq->count++;
}

void *removeEntry(PQ *pq){ /* Runtime: O(log n). Deletes node and reorganizes the queue */
	assert(pq!=NULL);
	void* root=pq->data[0];
	int index=0;
	int smallIndex=0;
	pq->data[index]=pq->data[pq->count-1];
	pq->count--;
	while(l(index)<pq->count){
		smallIndex=l(index);
		if(r(index)<pq->count){
			if(pq->compare(pq->data[l(index)],pq->data[r(index)])<0)
				smallIndex=l(index);
			else
				smallIndex=r(index);
		}
		if(pq->compare(pq->data[smallIndex],pq->data[index])<0){
			void* temp=pq->data[smallIndex];
			pq->data[smallIndex]=pq->data[index];
			pq->data[index]=temp;
			index=smallIndex;
		}
		else
			break;
	}
	return root;
}
