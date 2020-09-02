#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define SIZE 10
#define LENGTH 20
#define NODE struct node
#define ARRAY struct point

extern int counter;
extern int x;

struct node
{
		char name[LENGTH];
			int size;
				NODE *next;
};

struct point
{
		NODE *head;
		NODE *tail;
};

struct point array[4];

void add(char *tname, int tsize);
void cancel();
void list();
void search_size();
void free_them();
void change();
void list_rev();
void name_rev();
void read_f(char arg[], int key);
void save(char arg[], int key);
void *autosave();
void read_binary(char arg[]);
int rep();
extern pthread_mutex_t lock;
