#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 10
#define LENGTH 20
#define NODE struct node
#define ARRAY struct point

int counter=0;

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
void delete();
void list();
void search_size();
void free_them();
void change();
void read(char *name);
void save(char *name);
int rep();

int main(int argc,char *argv[]){
	if(argc==1){
		printf("The name of the file is missing!\n");
		return 1;
	}
	read(argv[1]);
	int x=1;
	while(x==1){
		printf("\n 1. Add Reservation\n 2. Remove Seated Party from List\n 3. Show Reservation List\n 4. Search for Table by Size\n 5. Change Your Reservation Group Size\n 0: Quit Program\n");
		int input,tsize;
		char tname[20];
		scanf("%d",&input);
		switch (input)
		{	
			case 1:
			{
				printf("Please enter your name:\n");
				scanf("%s",tname);
				if(rep(tname)==1)
					printf("You have already made a reservation\n");
				else if(rep(tname)==0){
					printf("Please enter your group size:\n");
					scanf("%d",&tsize);
					add(tname,tsize);
				}
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
			case 5:
			{
				change();
				break;
			}
			case 0:
			{
				save(argv[1]);
				free_them();
				x=0;
				break;
			}
			default:
			{
				printf("Command not recognized\n");
				break;
			}
		}
	}
}
void add(char *tname,int tsize){
	NODE *temp;
	int flag=-1;
	if((temp=(NODE *)malloc(sizeof(NODE)))==(NODE*)NULL){
			printf("No memory can be allocated\n");
			return;
	}
	strcpy(temp->name,tname); /*Puts the checked name into the name array */
	if(tsize<=2)
		flag=0;
	if(tsize<=4 && tsize>2)
		flag=1;
	if(tsize<=6 && tsize>4)
		flag=2;
	if(tsize>6)
		flag=3;
	temp->size=tsize;
	if(array[flag].head==NULL){ /*If node is at the head*/
		temp->next=array[flag].head;
		array[flag].head=temp;
		array[flag].tail=array[flag].head;
	}
	else{
		 array[flag].tail->next=temp;
		 temp->next=NULL;
		 array[flag].tail=temp;
	}
	counter++;
	return;
}

void delete(){
	int i;
	NODE *p,*q;
	int table;
	int flag=-1;
	if(counter==0){
		printf("No reservations have been made\n");
		return;
	}
	else{
		int check=0;
		printf("Enter the size of the table\n");
		scanf("%d",&table);
		if(table<=2)
			flag=1;
		if(table>2 || table<=4)
			flag=2;
		if(table>4 || table<=6)
			flag=3;
		if(table>6)
			flag=4;
		for(i=0;i<flag;i++){
			p=q=array[i].head;
			while(p!=NULL){
				if(p->size<=table){
					printf("%s's reservation for %d has been deleted\n",p->name,p->size);
					counter--;
					check=1;
					if(p==array[i].head)
						array[i].head=p->next;
					else
						q->next=p->next;
					free(p);
					return;
				}
				q=p;
				p=p->next;
			}
		}
		if(check==0)
			printf("No such reservation exists\n");
	}
}

void list(){
	NODE *p;
	int i;
	if(counter==0){
		printf("No reservations were made\n");
		return;
	}
	else{
		for(i=0;i<4;i++){	
			p=array[i].head;
			while(p!=NULL){ /* Goes through each reservation and prints them */
				printf("Name: %s Party Size: %d\n",p->name,p->size);
				p=p->next;
				}
		}
	}
	return;
}

int rep(char entry[20]){
	NODE *p;
	int i;
	for(i=0;i<4;i++){ /*checks if user input and saved reservations are the same */
		p=array[i].head;
		while(p!=NULL){	
			if(strcmp(entry,p->name)==0)
				return 1;
			else
				p=p->next;
		}
	}
	return 0;
}

void search_size(){
	NODE *p;
	int input;
	int check=1;
	int flag=(-1);
	if(counter==0){
		printf("No reservations have been made\n");
		return;
	}
	else{
		printf("Please enter the size of the table you are searching for\n");
		scanf("%d",&input);
		if(input<=2)
			flag=1;
		if(input<=4 && input>2)
			flag=2;
		if(input<=6 && input>4)
			flag=3;
		if(input>6)
			flag=4;
		for(int i=0;i<flag;i++){ /* Goes through size array to compare user imput with saved values */
			p=array[i].head;
			while(p!=NULL){
				if(p->size<=input){
					printf("Name: %s Size: %d\n",p->name,p->size);
					check=0;
				}
				p=p->next;
			}
		}
		if(check==1)
			printf("There are no reservations of that size\n");
		return;
	}
}	

void free_them(){
	NODE *p,*q;
	int i;
	for(i=0;i<4;i++){
		if(array[i].head!=NULL){
			if(array[i].head->next==NULL){
				printf("%s, Size: %d's reservation has been freed\n",array[i].head->name,array[i].head->size);
				free(array[i].head);
			}
			else{
				q=array[i].head;
				p=array[i].head->next;
				while(q!=NULL){
					printf("%s, Size: %d's reservation has been freed\n",q->name,q->size);
					free(q);
					q=p;
					if(p!=NULL)
						p=p->next;
				}
			}
		}
	}
}

void change(){
	NODE *p,*q;
	char original[10];
	int new,flag,i;
	printf("Please enter your name:\n");
	scanf("%s",original);
	printf("Please enter your new group size:\n");
	scanf("%d",&new);
	if(new<=2)
		flag=0;
	if(new>2 && new<=4)
		flag=1;
	if(new>4 && new<=6)
		flag=2;
	if(new>6)
		flag=3;
	for(i=0;i<counter;i++){
		p=q=array[i].head;
		while(p!=NULL){
			if(strcmp(p->name,original)==0){
				p->size=new;
				if(p==array[i].head)
					array[i].head=p->next;
				else
					q->next=p->next;
				if(array[flag].head==NULL){
					p->next=array[flag].head;
					array[flag].head=p;
					array[flag].tail=array[flag].head;
				}
				else{
					array[flag].tail->next=p;
					p->next=NULL;
					array[flag].tail=p;
				}
				return;
			}
			p=p->next;
		}
	}
	printf("Your reservation could not be found\n");
	return;
}

void read(char *name){
	FILE *fp;
	char tname[20];
	int tsize,i;
	fp=fopen(name,"r");
	if(fp==NULL)
		return;
	fseek(fp,46,SEEK_SET); /* Skips through the header */
	while(fscanf(fp,"%s %d",tname,&tsize)==2)
		add(tname,tsize);
	fclose(fp);
}

void save(char *name){
	FILE *fp;
	NODE *p;
	int i;
	fp=fopen(name,"w");
	if(fp==NULL)
		return;
	fprintf(fp,"Name:\t    Party Size: \n");
	fprintf(fp,"----------------------\n");
	for(i=0;i<4;i++){
		p=array[i].head;
		while(p!=NULL){
			fprintf(fp,"%s\t%d\n",p->name,p->size);
			p=p->next;
		}
	}
	fclose(fp);
	return;
}
