/*
Luke Manzitto
11/23/2020
Lab8 - Step1
Creates a file with random numbers between 0-19.
*/
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *fp;
    char buffer [sizeof(int)];
    int i;
    fp = fopen("testInput.txt", "w");
    for (i=0; i<100; i++){
        sprintf(buffer, "%d\n", rand()%20);
        fputs(buffer, fp);    
    }    
    fclose(fp);
    return 0;
}