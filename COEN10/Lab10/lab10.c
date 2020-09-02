#include <stdio.h>
#include <string.h>
#include <ctype.h>
int counter=0;
char list[10][20];
char word[20];
void task1();
void task2();
void task3();
void task4();
void print();
int main(){
	task1();
	task2();
	task3(list);
	task4();
}
void task1(){
	int i,j,k;
	printf("Please enter up to 10 words:\n");
	for(i=0;i<10;i++){ /* Loops through ten possible word inputs */
		if(scanf("%s",word)<1)
			i=10;
		else{
			if(counter==0)
				strcpy(list[counter],word);
			else{
				for(j=0;j<counter;j++){
					if(strcmp(word,list[j])<0){ /* compares words based on their alphabetical value */
						for(k=counter;k>j;k--)
							strcpy(list[k],list[k-1]);
						strcpy(list[j],word);
						j=counter;
					}
					else
						strcpy(list[counter],word);
				}
			}
			counter++;
		}
	}
	printf("Alphabetical Order:\n");
	print();
}
void task2(){
	char temp[20];
	int i;
	for(i=0;i<counter/2;i++){ /* switchs places of words to be in reverse order */
		strcpy(temp,list[i]);
		strcpy(list[i],list[counter-(1+i)]);
		strcpy(list[counter-(1+i)],temp);
	}
	printf("Reverse Order:\n");
	print();
}
void task3(char *p){
	int i,j;
	int length;
	for(i=0;i<counter;i++){ 
		length=strlen(list[i]);
		for(j=0;j<length;j++){
			if(list[i][j]>='A' && list[i][j]<='Z')
				list[i][j]+=32;
		}
	}
	printf("Capitalization Conversion:\n");
	print();
}
void task4(){
	int i,average;
	int lLength=0;
	int sLength=0;
	int sum=0;
	char shortest[20];
	strcpy(shortest,list[0]);
	char longest[20];
	strcpy(longest,list[0]);
	for(i=1;i<counter;i++){
		if(strlen(list[i])>strlen(longest)){ /* finds the longest word */
			strcpy(longest,list[i]);
			lLength=strlen(longest);
		}
		else if(strlen(list[i])<strlen(shortest)){ /* finds the shortest word */
			strcpy(shortest,list[i]);
			sLength=strlen(shortest);
		}
	}
	for(i=0;i<counter;i++)
		sum+=strlen(list[i]);
	average=sum/counter;
	printf("Shortest Word:\n");
	printf("%s, ",shortest);
	printf("%d\n",sLength);
	printf("Longest Word:\n");
	printf("%s, ",longest);
	printf("%d\n",lLength);
	printf("Average Length of Words:\n");
	printf("%d\n",average);
	printf("Words That Didn't Start with a Letter:\n");
	for(i=0;i<counter;i++){
		if(isalpha(list[i][0])==0) /* Checks to see if any words start with a non-letter */
			printf("%s\n",list[i]);
	}
}
void print(){
	int i;
	for(i=0;i<counter;i++){ /* prints all words inputted */
		printf("%s, ",list[i]);
		printf("\n");
	}
}
