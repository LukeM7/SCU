#include "global.h"

int counter=0;
int x=1;
int key;

struct point array[4];
pthread_mutex_t lock=PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char *argv[]){
	pthread_t thread;
	pthread_mutex_init(&lock,NULL);
	pthread_create(&thread,NULL,autosave,(void*)argv[2]);
	if(argc!=4){
		printf("The name of the file is missing!\n");
		return 1;
	}
	key=atoi(argv[3]);
	read_f(argv[1],key);
	int x=1,i;
	NODE *p;
	while(x==1){
		printf("\n 1. Add Reservation\n 2. Remove Seated Party from List\n 3. Show Reservation List\n 4. Search for Table by Size\n 5. Change Your Reservation Group Size\n 6. Show List Backwards\n 7. Show Names Backwards\n 8. Read Binary File\n 0. Quit Program\n");
		int input,tsize;
		char tname[20];
		scanf("%d",&input);
		switch(input)
		{
			case 1:
			{
				printf("Please enter your name: \n");
				scanf("%s",tname);
				if(rep(tname)==0){
					printf("Please enter your group size:\n");
					scanf("%d",&tsize);
					add(tname,tsize);
				}
				break;
			}
			case 2:
			{
				cancel();
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
			case 6:
			{
				for(i=3;i>=0;i--){
					p=array[i].head;
					list_rev(p);
				}
				break;
			}
			case 7:
			{
				for(i=0;i<4;i++){
					p=array[i].head;
					name_rev(p);
				}
				break;
			}
			case 8:
			{
				read_binary(argv[2]);
				break;
			}
			case 0:
			{
				pthread_mutex_lock(&lock);
				pthread_cancel(thread);
				pthread_mutex_unlock(&lock);
				save(argv[1],key);
				for(i=0;i<4;i++){
					p=array[i].head;
					free_them(p);
				}
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

