#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(void){
	int i;
	int counter = 0;
	int percentage = 0;
	srand((int) time(NULL));
	for(i=0;i<10;i++){ /*Running a multiplication set loop ten times with user input */
		int num1 = rand() % 13;
		int num2 = rand() % 13;
		int user;
		printf("%d * ",num1);
		printf("%d\n",num2);
		scanf("\n%d",&user);
		if(user == num1 * num2){ /*checking the user's answer */
			printf("Correct!\n");
			counter++;
		}
		else
			printf("Incorrect\n");
	}
	printf("You got %d%%", counter*10); /*will show percentage of user's answers that were correct */
}
