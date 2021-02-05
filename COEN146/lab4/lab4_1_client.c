//Luke Manzitto
//2/4/2021
//Lab4 - Step 1
// Client side of a TCP/IP connection
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define _OPEN_SYS_SOCK_IPV6
#include <arpa/inet.h>

#define BUFFER_SIZE 256


int main(int argc, char* argv[]){
    if(argc != 2){
        printf("Bad args %s <port num>\n",argv[1]);
        return -1;
    }

    int port_id = atoi(argv[1]);
    int client_fd = socket(AF_INET,SOCK_STREAM,0);
    char* ip = "127.0.0.1";
    char* file = "test.txt";

    //IP and port stuff
    struct sockaddr_in sockaddr;
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(port_id);
    sockaddr.sin_addr.s_addr = inet_addr(ip);

    connect(client_fd,(struct sockaddr*)&sockaddr,sizeof(sockaddr));
    printf("connected\n");
    send(client_fd,file,strlen(file)+1,0);

    //Writes data recieved to new file
    FILE* fp = fopen("ServertoClient.txt","w");
    void* in_buffer = (void*)malloc(BUFFER_SIZE);

    int write = 0;
    while(write = recv(client_fd,in_buffer,BUFFER_SIZE,0)){
        fwrite(in_buffer,write,1,fp);
    }
    
    fclose(fp);
    free(in_buffer);
    close(client_fd);
    return 0;
}