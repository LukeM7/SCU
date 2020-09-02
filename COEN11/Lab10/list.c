#include "global.h"

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

void cancel(){
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

void free_them(NODE *p){
	int i;
	if(p==NULL)
		return;
	free_them(p->next);
	printf("%s, Size: %d's reservation has been freed\n",p->name,p->size);
	free(p);
	return;
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
					array[i].head=p->next;																																			else
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

void name_rev(NODE *p){
	int i;
	if(counter==0){
		printf("No reservations have been made\n");
		return;
	}
	else{
		if(p==NULL)
			return;
		for(i=strlen(p->name);i>=0;i--)
			printf("%c",p->name[i]);
		printf("\n");
		name_rev(p->next);
	}	
	return;
}

void list_rev(NODE *p){
	int i;
	if(counter==0){
		printf("No reservations have been made\n");
		return;
	}
	else{
		if(p==NULL)
			return;
		list_rev(p->next);
		printf("Name: %s Size: %d\n",p->name,p->size);
	}
	return;
}


