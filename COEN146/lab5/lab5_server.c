//Luke Manzitto
//02/08/2021
//Lab 5 - Server
//Server side of a UDP connection
#include "lab5.h"

//getChecksum()
int getChecksum(Packet packet) {
    packet.header.cksum = 0;
    int checksum = 0;
    char *ptr = (char *)&packet;
    char *end = ptr + sizeof(Header) + packet.header.len;
//Find the error (if any) from the remaining part getChecksum() function and correct it
//******STUDENT WORK****** 
    while (ptr < end) {
        checksum ^= *ptr++;
    }
    return checksum;
}

// printPacket()
void printPacket(Packet packet) {
    printf("Packet{ header: { seq_ack: %d, len: %d, cksum: %d }, data: \"",
            packet.header.seq_ack,
            packet.header.len,
            packet.header.cksum);
    fwrite(packet.data, (size_t)packet.header.len, 1, stdout);
    printf("\" }\n");
}

//Server sending ACK to the client
void serverSend(int sockfd, const struct sockaddr *address, socklen_t addrlen, int seqnum) {
    Packet packet;
	//Prepare the packet headers
	//send the packet
    //******Student Work******
    printf("\ncheck\n");
    packet.header.seq_ack = seqnum;
    packet.header.len = sizeof(packet.data);
	packet.header.cksum = getChecksum(packet);
    
    sendto(sockfd,(void*)&packet,sizeof(packet),0,address,addrlen);
    printf("\t Server: sending ACK %d, checksum %d\n", packet.header.seq_ack, packet.header.cksum);
}

//Server receiving packet
Packet serverReceive(int sockfd, struct sockaddr *address, socklen_t *addrlen, int seqnum) {
    Packet packet;
    while (1) {
        //recv packets from the client
		//******Student Work******
        int bytesRecv = recvfrom(sockfd,(void*)&packet,sizeof(packet),0,address,addrlen);
        // Print received packet
        printPacket(packet);

        if (packet.header.cksum != getChecksum(packet)) {
            printf("Bad checksum, expected checksum was: %d\n", getChecksum(packet));
            serverSend(sockfd, address, *addrlen, !seqnum);
        } else if (packet.header.seq_ack != seqnum) {
            printf("Bad seqnum, expected sequence number was:%d\n", seqnum);
            serverSend(sockfd,address,*addrlen,!seqnum);
        } else {
            printf("Good packet\n");
            serverSend(sockfd,address,*addrlen,seqnum);
            break;
        }
    }
    return packet;
}


int main(int argc, char *argv[]) {
    // check arguments
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <port> <outfile>\n", argv[0]);
        exit(1);
    }
    // seed the RNG
    srand((unsigned)time(NULL));
    
    int port = atoi(argv[1]);
    // create a socket
	//******STUDENT WORK******
    int sockfd = socket(AF_INET,SOCK_DGRAM,0);
    // initialize the server address structure using argv[1]
    struct sockaddr_in address;
	//******STUDENT WORK******
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    socklen_t address_size = (socklen_t)sizeof(address);
    // bind the socket
	// [Question]: Do we need to bind the socket on the client side? Why?/Why not?
	//******STUDENT WORK******
    bind(sockfd,(struct sockaddr*)&address,address_size);
    // open file using argv[2]
	//******STUDENT WORK******
    FILE *fp = fopen(argv[2],"w");
    // get file contents from client
    bool seqnum = false;
    Packet packet;
    struct sockaddr_in clientaddr;
    socklen_t clientaddr_len = sizeof(clientaddr);
    do {
        packet = serverReceive(sockfd,(struct sockaddr*)&clientaddr,&clientaddr_len,seqnum);
        fwrite(packet.data,packet.header.len,1,fp);
        seqnum = !seqnum;
	//******STUDENT WORK******
    } while (packet.header.len != 0);

    fclose(fp);
    close(sockfd);
    return 0;
}
