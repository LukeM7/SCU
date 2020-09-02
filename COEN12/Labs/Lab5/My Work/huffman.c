#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "pack.h"
#include "pqueue.h"

typedef struct node NODE; /* Defines node struct */

int hopNumber(NODE *leaf){ /* Runtime: O(h). Counts the distance from the leaf to the root */
	int hops=0;
	while(leaf->parent!=NULL){
		leaf=leaf->parent;
		hops++;
	}
	return hops;
}

int compare(NODE *first,NODE *second){ /* Runtime: O(1). Compares data from two nodes */
	return (first->count < second->count) ? -1 : (first->count >second->count);
}

int main(int argc, char *argv[]){ 
	int i;
	FILE *fp=fopen(argv[1],"r"); /* Opens and reads file to fp pointer */
	if(fp==NULL)
		return 0;
	int occurances[257] = {0}; /* Creates an occurances array */
	do{
		int c;
		c=fgetc(fp);
		if(feof(fp))
			break;
		occurances[c]++;
	}while (1); /* Assigns numbers to array indexes */
	PQ *pqueue = createQueue(compare); /* Creates the priority queue */
	NODE *leaves[257]={0};
	for(i=0;i<257;i++)
		leaves[i]=NULL;
	for(i=0;i<257;i++){ 
		if(occurances[i]>0){
			NODE *new = malloc(sizeof(NODE));
			new->count=occurances[i];
			new->parent=NULL;
			addEntry(pqueue,new);
			leaves[i]=new;
		}
	}
	NODE *zeroCount = malloc(sizeof(NODE)); /* adds a no count node to the last slot */
	zeroCount->count = 0;
	zeroCount->parent = NULL;
	addEntry(pqueue,zeroCount);
	leaves[256] = zeroCount;
	while(numEntries(pqueue)>1){ /* combines the priority trees until only the huffman tree remains */
		NODE *first = removeEntry(pqueue);
		NODE *second = removeEntry(pqueue);
		NODE *third = malloc(sizeof(NODE));
		third->count= (first->count + second->count);
		third->parent=NULL;
		first->parent=third;
		second->parent=third;
		addEntry(pqueue,third);
	}
	for(i=0;i<257;i++){ /* Prints out proper nodes */
		if(leaves[i]!=NULL){
			int numberOf;
			numberOf=hopNumber(leaves[i]);
			if(isprint(i))
				printf("%c: %d x %d bits = %d\n",i,occurances[i],numberOf,occurances[i]*numberOf);
			else
				printf("%03o: %d x %d bits = %d\n",i,occurances[i],numberOf,occurances[i]*numberOf);
		}
	}
	pack(argv[1],argv[2],leaves); /* packs the huffman tree */
	return 0;
}

