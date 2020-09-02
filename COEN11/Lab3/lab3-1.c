#include <stdio.h>
#include <string.h>

#define SIZE 10
#define LENGTH 20

int counter=0;
struct reservations{
	char name[LENGTH];
	int size;
};

struct reservations info[SIZE];

void add();
void delete();
void list();
void search_size();
int rep();

int main(){
	int x=1;
	while(x==1){
		printf("\n1: Add Reservation\n 2. Remove Seated Party from List\n 3. Show Reservation List\n 4. Search for Table by Size\n 0: Quit Program\n");
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
			case 4:
			{
				search_size();
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
	struct reservations *p=info;
	char temp[20];
	while(p->size!=0) /* Sets the position of the pointer at a value not taken */
		p++;
	printf("Please type your name\n");
	scanf("%s",temp); 
	rep(temp); /* Uses temp variable so as not to put a repeat in array */
	if (rep(temp)==1)
		printf("You have already made a reservation\n");
	else{
		if(counter!=SIZE){;
			strcpy(p->name,temp); /* Puts the checked name into the name array */ 
			printf("How many people will be in your party?\n");
			scanf("%d",&p->size);
			printf("Your table has been reserved\n");
			p++;
			counter++;
		}
		else
			printf("No more room for reservations\n");
	}
}
void delete(){
	struct reservations *p=info;
	int table;
	printf("Enter the size of the table\n");
	scanf("%d",&table);
	for(int i=0;i<counter;i++){ /*Goes through every reservation */
		if(p->size<=table){
			printf("Reservation deleted :%s %d\n",p->name,p->size);
			for(int j=i;j<counter;j++){ /* Goes through the reservations again */
					strcpy(p->name,(p+1)->name); /* Copies over deleted reservation */
					p->size=(p+1)->size;
					p++;
				}
			counter--;
			break;
		}
		else
			printf("No tables are available\n");
	}
}

void list(){
	struct reservations *p=info;
	if (counter==0){
		printf("No reservations have been made\n");
	}
	else{	
		for(int i=0;i<counter;i++){ /* Goes through each reservation and prints them */
			printf("Name:%s Party Size: %d\n",p->name,p->size);
			p++;
		}
	}
}

int rep(char entry[20]){
	struct reservations *p=info;
	int i;
	for(i=0;i<counter;i++){ /*checks if user input and saved reservations are the same */
		if(strcmp(entry,p->name)==0)
			return 1;
		p++;
	}
	return 0;
}

void search_size(){
	struct reservations *p=info;
	int input;
	printf("Please enter the size of the table you are searching for\n");
	scanf("%d",&input);
	for(int i=0;i<counter;i++){ /* Goes through size array to compare user imput with saved values */
		if(p->size<=input)
			printf("Name: %s Size: %d",p->name,p->size);
		p++;
	}
}
