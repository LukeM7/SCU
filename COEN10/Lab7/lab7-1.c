#include <stdio.h>
#include <string.h>
int main (void)
{
	char schedule[5][20];
	char name[20];
	char letter;
	int flag=0;
	int i,j,input;
	int x=0;
	int counter=0;
	printf("Option 1: Add lesson\nOption 2: Delete Lesson\nOption 3: List Lesson\nOption 4: List Names Starting with First Letter\nTo exit press 9\n");
	while(x==0)
	{
		scanf("%d",&input);
		switch (input)
		{
			case 1: /* Will check if lessons are full and add appointments */
			{
				if(counter==5)
					printf("All lessons are full\n");
				else
				{
					printf("Please enter your name here: \n");
					scanf("%s",schedule[counter]);
					printf("%d PM has been selected\n",counter+1);
					counter++;
					break;
				}
				break;
			}
			case 2: /* Will Go through array and delete user time input	*/
			{
				if(counter==0)
					printf("There are no classes currently scheduled\n");
				else
				{
					printf("Please enter your name: \n");
					scanf("%s",name);
					for(i=0;i<5;i++)
					{
						if (strcmp(name,schedule[i])==0) /* Compares user input with current schedule */
						{
							counter--;
							for(j=i;j<5;j++)
							{
								if(j!=4)
									strcpy(schedule[j],schedule[j+1]);
								else
									schedule[j][0]='\0';
							}
						}
					}
				}
				break;
			}
			case 3: /*Checks if lessons are filled and if not will list which are and aren't */
			{
				if(counter==0)
					printf("No lessons have been taken\n");
				else
				{
					for(i=0;i<5;i++)
					{
						if(schedule[i][0]=='\0') /* Checks to see if the schedule is empty */
							printf("%d PM is free\n",i+1);
						else
							printf("%d PM has been taken by %s\n",i+1,schedule[i]);
					}
				}
				break;
			}
			case 4:
			{
				flag=0;
				if(counter==0){
					printf("No times are currently scheduled\n");
				}
				else if(counter!=0)
				{	
					printf("Please enter first letter of name: \n");
					getchar();
					scanf("%c",&letter);
					for(i=0;i<5;i++) /* Loops through array to see what's available */
					{
						if(letter==schedule[i][0]){ /*Compares letter user inputed to the first letter of each schedule row */
							printf("%s\n",schedule[i]);
							flag=1;
						}
					}
					if(flag==0)
						printf("Letter not recognized\n");
				}
				break;
			}	
			case 9:
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
