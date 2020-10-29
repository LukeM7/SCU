/*
 * Name: Luke Manzitto
 * Date: 10/19/2020
 * Title: Lab4 - step 3
 * Description: This program computes the product of two matrices and displays the output
*/


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define MATRIX_ROW_DIMENSION 3
#define MATRIX_COLUMN_DIMENSION 3


//Could've done without the struct and just used int **matrix
typedef struct matrix{
	int row_size;
	int column_size;
	int **index;
} matrix;

//Arg struct to pass to thread as an arguement
typedef struct args{
	matrix *m1;
	matrix *m2;
	matrix *result;
	int row;
} args;


matrix *CreateMatrix();
void DeleteMatrix(matrix*);
args *SetArgs(matrix*,matrix*,matrix*,int);
void PrintMatrix(matrix*);

void* multiply(void*);

int main(){
	srand(time(NULL));
	int i,j;
	
	pthread_t threads[MATRIX_ROW_DIMENSION];
	matrix *m1 = CreateMatrix();
	matrix *m2 = CreateMatrix();
	matrix *m3 = CreateMatrix();
	//printf("%d",sizeof(*m1));
	//printf("\nM3 column size: %d\n",m3->column_size);
	printf("\n Matrix 1 \n");
	PrintMatrix(m1);
	printf("\n Matrix 2 \n");
	PrintMatrix(m2);
	//Sets arg struct, inits at row 0
	args *arg = SetArgs(m1,m2,m3,0);
	//creates threads and multiplies m1 and m2, storing the result in m3
	for(i=0;i<MATRIX_ROW_DIMENSION;++i){
		pthread_create(&threads[i],NULL, multiply, (void*)arg);
		usleep(i);
	}
	// joins threads back to main
	for(i=0;i<MATRIX_ROW_DIMENSION;++i)
		pthread_join(threads[i],NULL);
	free(arg);
	printf("\nMatrix 3\n");
	PrintMatrix(m3);
	DeleteMatrix(m1);
	DeleteMatrix(m2);
	DeleteMatrix(m3);
	printf("\nSUCCESS\n");
	return;
}

//Allocates memory for a matrix
matrix *CreateMatrix(){
	int i, j;
	matrix* m = (matrix*)malloc(sizeof(*m));
	m->row_size = MATRIX_ROW_DIMENSION;
	m->column_size = MATRIX_COLUMN_DIMENSION;
	m->index = malloc(sizeof(int*) * MATRIX_ROW_DIMENSION);
	for(i=0;i<MATRIX_ROW_DIMENSION;++i) 
		m->index[i] = malloc(sizeof(int) * MATRIX_ROW_DIMENSION);
	printf("\nMatrix successfully malloced\n");
	
	for(i=0;i<m->row_size;i++){
		for(j=0;j<m->column_size;++j){
			*(*(m->index+j) + i) = rand() % 20;
		}
	}
	return m;
}

// frees matrix memory
void DeleteMatrix(matrix *m){
	int i;
	for(i=0;i<MATRIX_ROW_DIMENSION;++i)
		free(m->index[i]);
	free(m->index);
	free(m);
	printf("\nMatrix struct deleted\n");
	return;
}

// Allocates arguement struct
args *SetArgs(matrix* m1, matrix* m2, matrix* result, int row_index){
	args *arg = malloc(sizeof(*arg));
	arg->m1 = malloc(sizeof(*m1));
	arg->m2 = malloc(sizeof(*m2));
	arg->result = malloc(sizeof(*result));
	arg->row = row_index;
	arg->m1 = m1;
	arg->m2 = m2;
	arg->result = result;
	return arg;
}

void PrintMatrix(matrix *m){
	int i,j;
	for(i=0;i<MATRIX_ROW_DIMENSION;++i){
		printf("\n");
		for(j=0;j<MATRIX_COLUMN_DIMENSION;++j){
			printf("|| %d || ",*(*(m->index + j) +i));
		}
		printf("\n");
	}
	return;
}

void *multiply(void* arg){
	int i,j;
	args *newArg = (args*)arg;
	if(newArg == NULL) printf("\nFailed cast to newArg\n");
	//printf("\ncheck row: %d\n",newArg->row);
	//printf("\ncheck:%d\n",newArg->result->column_size);
	//printf("\nMatrix 1 Check\n");
	//PrintMatrix(newArg->m1);
	//printf("\nMatrix 2 Check\n");
	//PrintMatrix(newArg->m2);
	
	for(i=0;i<newArg->result->row_size;++i){
		int new = 0;
		for(j=0;j<newArg->result->column_size;++j){
			new += newArg->m1->index[j][newArg->row] * newArg->m2->index[i][j];
			//printf("\n%d * %d\n",newArg->m1->index[j][newArg->row], newArg->m2->index[i][j]);
		}
		//printf("\nNew: %d\n",new);
		newArg->result->index[i][newArg->row] = new;
	}
	newArg->row++;
	return;
}
