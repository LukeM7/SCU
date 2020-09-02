# ifndef SET_H
# define SET_H

struct info{
	int age;
	int id;
};

typedef struct set{
	int count;
	int length;
	struct info *data;
}SET;

SET *createDataSet(int maxElts);

void destroyDataSet(SET* sp);

int searchAge(SET *sp, int x);

void insertion(SET *sp, int x, int y);

void deletion(SET *sp, int x);

int maxAgeGap(SET*sp, int max, int min);

# endif /* SET_H */
