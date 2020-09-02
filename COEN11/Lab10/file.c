#include "global.h"

void read_f(char arg[], int key){
	FILE *fp;
	char tname[20],buffer[200];
	int tsize,i;
	fp=fopen(arg,"r");
	if(fp==NULL)
		return;
	fseek(fp,46,SEEK_SET); /* Skips through the header */
	while(fgets(buffer,100,fp)!=NULL){
		for(i=0;i<strlen(buffer);i++)
			buffer[i]^=key;
		sscanf(buffer,"%s\t%d",tname,&tsize);
		add(tname,tsize);
	}
	fclose(fp);
}

void save(char arg[], int key){
	FILE *fp;
	NODE *p;
	int i,j;
	char buffer[200];
	fp=fopen(arg,"w");	
	if(fp==NULL)
		return;
	fprintf(fp,"Name:\t    Party Size: \n");
	fprintf(fp,"----------------------\n");
	for(i=0;i<4;i++){
		p=array[i].head;
		while(p!=NULL){
			sprintf(buffer,"%s\t%d",p->name,p->size);
			for(j=0;j<strlen(buffer);j++)
				buffer[j]^=key;
			fprintf(fp,"%s\t%d\n",p->name,p->size);
			p=p->next;																							
		}		
	}
	fclose(fp);
	return;
}

void* autosave(void *arg){
	while(1){
		pthread_mutex_lock(&lock);
		printf("Autosave complete\n");
		int i;
		FILE *fp;
		fp=fopen((char *)arg,"wb");
		NODE *p;
		for(i=0;i<4;i++){
			p=array[i].head;
			while(p!=NULL){
				fwrite(p,sizeof(NODE),1,fp); /* Writes to autosave file */
				p=p->next;
			}
		}
		fclose(fp);
		pthread_mutex_unlock(&lock);
		sleep(15);
	}
}

void read_binary(char arg[]){
	FILE *fp;
	NODE p;
	int ret;
	pthread_mutex_lock(&lock);
	fp=fopen(arg,"rb");
	if(fp==NULL){
		printf("File is empty\n");
		pthread_mutex_unlock(&lock);
		return;
	}
	while((ret=fread(&p,sizeof(NODE),1,fp)>0))
		printf("Name: %s  Party Size: %d\n",p.name,p.size); /* Prints autosave file */
	fclose(fp);
	pthread_mutex_unlock(&lock);
	return;
}
