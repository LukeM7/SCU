//Luke Manzitto
//2/4/2021
//Lab 4 - Step 3
// Modifies the TCP/IP server to allow threading with multiple connections

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#define _OPEN_SYS_SOCK_IPV6
#include <arpa/inet.h>

#define BUFFER_SIZE 256
#define MAX_CONNECTIONS 5

void* go(void* arg){
    int socket = *(int*)arg;
        
    // Buffers for reading/writing from socket
    void* out_buffer = (void*)malloc(BUFFER_SIZE);
    void* in_buffer = (void*)malloc(BUFFER_SIZE);
    printf("check\n");
    recv(socket,in_buffer,BUFFER_SIZE,0);
    printf("Recieved message: %s",(char*)in_buffer);

    //buffer now holds file name desired by client
    FILE* fp;
    fp = fopen((char*)in_buffer,"r");
    if(fp == NULL){
        printf("FIle error\n");
        exit(EXIT_FAILURE);
    }

    int write = 0;
    while(write = fread(out_buffer,1,BUFFER_SIZE,fp)){
        send(socket,out_buffer,write,0);
    }

    fclose(fp);
    free(in_buffer);
    free(out_buffer);
    close(socket);
}


int main(int argc, char* argv[]){
    //getting port number
    if(argc != 2){
        printf("Missing args %s <port num>\n",argv[0]);
        return -1;
    }

    pthread_t thread;

    int port_id = atoi(argv[1]);

    int server_fd;
    if((server_fd = socket(AF_INET,SOCK_STREAM,0)) < 0){
        perror("cannot create socket");
        return -1;
    }
    
    // socket setup stuff
    struct sockaddr_in sockaddr;
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(port_id);
    sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    //binding socket
    bind(server_fd,(struct sockaddr*)&sockaddr,(socklen_t)sizeof(sockaddr));

    //listening
    listen(server_fd,MAX_CONNECTIONS);
    socklen_t sockaddr_size = sizeof(sockaddr);
    int new_socket;
    sleep(MAX_CONNECTIONS);

    //connections
    while(new_socket = accept(server_fd,(struct sockaddr*)&sockaddr,&sockaddr_size)){
        int connection = new_socket;
        printf("Successful connections with socket %d, beginning transfer\n",port_id);
        pthread_create(&thread,NULL,go,(void*)&connection);

        pthread_join(thread,NULL);    
    }


    close(server_fd);
    return 0;
}