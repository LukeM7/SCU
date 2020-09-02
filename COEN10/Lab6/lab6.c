#include <stdio.h>
int main (void)
{
	int lessons[5] = {0,0,0,0,0};
	int i,input;
	int x=0;
	int counter=0;
	printf("Option 1: Add lesson\nOption 2: Delete Lesson\nOption 3: List Lesson\nTo exit press 9\n");
	while(x==0)
	{
		scanf("%d",&input);
		switch (input)
		{
			case 1: /* Will check if lessons are full and add appointments */
			{
				if(counter==5)
					printf("All lessons are full");
				else
					for(i=0;i<5;i++)
					{
						if(lessons[i]==0)
						{
							printf("%d PM has been selected\n",i+1);
							lessons[i]=1;
							counter++;
							break;
						}
					}
				break;
			}
			case 2: /* Will Go through array and delete user time input	*/
			{
				printf("Input time: ");
				scanf("%d",&input);
				if(lessons[input-1]==1)
				{
					printf("Lesson at %d PM has been deleted",input);
					lessons[input-1]=0;
				break;
				}
				else
					printf("Schedule is clear\n");
				break;
			}
			case 3: /*Checks if lessons are filled and if not will list which are and aren't */
			{
				if(counter==0)
					printf("All lessons have been taken");
				else

					for(i=0;i<5;i++) /* Loops through array to see what's available */
					{
						if(lessons[i]==0)
							printf("%d PM is available\n",i+1);
						else
							printf("%d PM is taken\n",i+1);
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
				printf("Incorrect Input");
				break;
			}
		}
	}
}
