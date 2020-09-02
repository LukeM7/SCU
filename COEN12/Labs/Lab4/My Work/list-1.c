#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct node{
	void *data;
	struct node *next;
	struct node *prev;
}NODE;

typedef struct list{
	int count;
	NODE *head;
	int (*compare)();
}LIST;

int i;

LIST *createList(int(*compare)()){ /* O(1) */
	LIST *lp;
	lp=malloc(sizeof(LIST));
	assert(lp!=NULL);
	lp->count=0;
	lp->head=malloc(sizeof(NODE));
	lp->head->next=lp->head;
	lp->head->prev=lp->head; /* make list circular */
	lp->compare=compare;   
	return lp;
}

void destroyList(LIST *lp){ /* O(n) */
	assert(lp!=NULL);
	while(lp->count>0)
		removeLast(lp);
}

int numItems(LIST *lp){ /* O(1) */
	assert(lp!=NULL);
	return lp->count;
}

void addFirst(LIST *lp, void *item){ /* O(1) */
	struct node *newNode = malloc(sizeof(NODE));
	newNode->data=item;
	newNode->next=lp->head->next;
	lp->head->next=newNode;
	newNode->prev=lp->head;
	newNode->next->prev=newNode; /*adds new node to beginning of list */
	lp->count++;
}

void addLast(LIST *lp, void *item){ /* O(1) */
	struct node *new = malloc(sizeof(NODE));
	new->data=item;
	new->next=lp->head;
	new->prev=lp->head->prev;
	lp->head->prev=new;
	new->prev->next=new; /* adds new node to end of list */
	lp->count++;
}

void *removeFirst(LIST *lp){ /* O(1) */
	assert(lp->count>0);
	struct node *first=lp->head->next;
	void *ndata=first->data;
	lp->head->next=first->next;
	first->next->prev=lp->head;
	free(first);
	lp->count--;
	return ndata;
}

void *removeLast(LIST *lp){ /* O(1) */
	assert(lp->count>0);
	struct node *last=lp->head->prev;
	void *ndata = last->data;
	last->prev->next=lp->head;
	lp->head->prev=last->prev;
	free(last);
	lp->count--;
	return ndata;
}

void *getFirst(LIST *lp){ /* O(1) */
	assert(lp->count>0 && lp!=NULL);
	return lp->head->next->data;
}

void *getLast(LIST *lp){ /* O(1) */
	assert(lp->count>0 && lp!=NULL);
	return lp->head->prev->data;
}

void removeItem(LIST *lp, void *item){ /* O(n) */
	assert(lp->compare!=NULL && lp->count>0 && item!=NULL);
	struct node *remove = lp->head->next;
	while(remove!=lp->head){
		if((*lp->compare)(remove->data,item)==0){
			remove->prev->next=remove->next;
			remove->next->prev=remove->prev;
			free(remove);
			lp->count--;
			break;
		}
		remove=remove->next;
	}
}

void *findItem(LIST *lp, void *item){ /* O(n) */
	assert(lp!=NULL);
	struct node *search = lp->head->next;
	while(search!=lp->head){
		if((*lp->compare)(search->data,item)==0)
			return search->data;
		search=search->next;
	}
	return NULL;
}

void *getItems(LIST *lp){ /* O(n) */
	assert(lp!=NULL);
	int j=0;
	void **array;
	array=malloc(sizeof(void*)*lp->count);
	NODE *p=lp->head->next;
	assert (array!=NULL);
	while(p!=lp->head){
		array[j]=p->data;
		p=p->next;
		j++;
	}
	return array;
}
