#include <stdio.h>
#include <string.h>
char schedule[5][20];
char name[20];
char letter;
char phone[5][10];
int flag=0;
int i,j,input,groupsz;
int group[5];
int x=0;
int counter=0;
void add();
void delete();
void list();
void names();
void groupsize();
int main(){
	printf("Option 1: Add lesson\nOption 2: Delete Lesson\nOption 3: List Lesson\nOption 4: Show Names- Letter\nOption 5: Show Names- Group Size\nTo exit press 9\n");
	while(x==0)
	{
		scanf("%d",&input);
		switch (input)
		{
			case 1: /* Will check if lessons are full and add appointments */
			{
				add();
				break;
			}
			case 2: /* Will Go through array and delete user time input	*/
			{
				delete();
				break;
			}
			case 3: /*Checks if lessons are filled and if not will list which are and aren't */
			{
				list();
				break;
			}
			case 4: /*Searches names by first letter */
			{
				names();
				break;
			}
			case 5: /* Searches names by group size */
			{
				groupsize();
				break;
			}
			case 9: /* Exits the program */
			{
				x=1;
				break;
			}
			default:
			{
				printf("Incorrect Input\n");
				break;
			}
		}
	}
}
void add(){
	if(counter==5) /* Checks if lessons are full */
		printf("All lessons are full\n");
	else
	{
		printf("Please enter your name here: \n");
		scanf("%s",schedule[counter]);
		for(i=0;i<5;i++){ /* Checks to see if name has already been input */
			if(strcmp(schedule[counter],schedule[i])==0 && counter>0){
				printf("You have already been scheduled\n");
				return;
			}
		}
		printf("Please enter your phone number here: \n");
		scanf("%s",phone[counter]);
		printf("Please enter the size of your group here: \n");
		scanf("%d",&group[counter]);
		if(group[counter]<=0)
			printf("Your group is too small\n");
		else if(group[counter]>5)
			printf("Your group is too large\n");
		else{
			printf("%d PM has been selected\n",counter+1);
			counter++;
		}
	}
}
void delete(){
	if(counter==0)
		printf("No lessons have been scheduled\n");
	else{
		printf("Please enter your name here: \n");
		scanf("%s",name);
		for(i=0;i<5;i++){ /* Finds what name in schedule matches user input */
			if(strcmp(name,schedule[i])==0){
				counter--;
				for(j=i;j<5;j++){ /* Shifts everything up 1 spot in the schedule array */
					if(j!=4){
						strcpy(schedule[j],schedule[j+1]);
						strcpy(phone[j],phone[j+1]);
						group[j]=group[j+1];
					}
					else{ /* Deletes the indivual name in schedule array */
						schedule[j][0]='\0';
						phone[j][0]='\0';
						group[j]=0;
					}
				}
			}
		}
	}
}
void list(){
	if(counter==0)
		printf("No lessons have been scheduled\n");
	else{
		for(i=0;i<5;i++){ /* Checks to see what has been filled in the schedule array */
			if(schedule[i][0]=='\0')
				printf("%d PM is free\n",i+1);
			else
				printf("%d PM has been taken by %s,%s,%d people\n",i+1,schedule[i],phone[i],group[i]);
		}
	}
}
void names(){
	flag=0;
	if(counter==0)
		printf("No times are currently scheduled\n");
	else if(counter!=0){
		printf("Please enter first letter of name: \n");
		getchar();
		scanf("%c",&letter);
		for(i=0;i<5;i++){ /* Matches the letter with the first letter of the schedule array */
			if(letter==schedule[i][0]){
				printf("%s\n",schedule[i]);
				flag=1;
			}
		}
		if(flag==0)
			printf("Letter not recognized\n");
	}
}
void groupsize(){
	flag=0;
	if(counter==0)
		printf("No times are currently scheduled\n");
	else if(counter!=0){
		printf("Please enter group size: \n");
		getchar();
		scanf("%d",&groupsz);
		for(i=0;i<5;i++){ /* Checks if the group size input is equal to the group array */
			if(groupsz==group[i]){
				printf("%s\n",schedule[i]);
				flag=1;
			}
		}
		if(flag==0)
			printf("Group size not found\n");
	}
}
