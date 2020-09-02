# ifndef SET_H
# define SET_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define startingLength 1000

struct info{
	int age;
	int id;
};

typedef struct set{
	int count;
	int length;
	struct info *data;
}SET;

SET *createDataSet();

void destroyDataSet(SET *sp);

int searchAge(SET *sp, int x);

int searchID(SET *sp, int y);

void insertion(SET *sp, int x, int y);

void deletion(SET *sp, int x);

int maxAgeGap(SET *sp, int max, int min);

#endif /* SET_H */
