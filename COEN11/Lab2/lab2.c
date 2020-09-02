#include <stdio.h>
#include <string.h>

#define SIZE 10
#define LENGTH 20

char name[SIZE][LENGTH];
int size[SIZE];
int counter=0;

void add();
void delete();
void list();

int main(){
	int x=1;
	while(x==1){
		printf("\n1: Add Reservation\n 2. Remove Seated Party from List\n 3. Show Reservation List\n 0: Quit Program\n");
		int input;
		scanf("%d",&input);
		switch (input)
		{
			case 1:
			{
				add();
				break;
			}
			case 2:
			{
				delete();
				break;
			}
			case 3:
			{
				list();
				break;
			}
			case 0:
			{
				x=0;
				break;
			}
		}
	}
}
void add(){
	if(counter!=SIZE){
		counter++;
		printf("Please type your name\n");
		scanf("%s",name[counter-1]);
		printf("How many people will be in your party?\n");
		scanf("%d",&size[counter-1]);
	}
	else
		printf("No more room for reservations\n");
}

void delete(){
	int table;
	printf("Enter the size of the table\n");
	scanf("%d",&table);
	for(int i=0;i<counter;i++){
		if(size[i]<=table){
			printf("Reservation deleted :%s %d\n",name[i],size[i]);
			for(int j=i;j<counter;j++){
					strcpy(name[j],name[j+1]);
					size[j]=size[j+1];
				}
			counter--;
			break;
		}
		else
			printf("No tables are available\n");
	}
}

void list(){
	if (counter==0){
		printf("No reservations have been made\n");
	}
	else{	
		for(int i=0;i<counter;i++){
			printf("%s  %d\n",name[i],size[i]);
		}
	}
}
