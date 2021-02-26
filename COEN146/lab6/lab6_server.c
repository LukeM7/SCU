//Luke Manzitto
//2/23/2021
//Lab 6 - Server
// Server side of server-client connection using the select function

//Lab6 Server
#include "lab6.h"

//getChecksum()
int getChecksum(Packet packet) {
    packet.header.cksum = 0;
    int checksum = 0;
    char *ptr = (char *)&packet;
    char *end = ptr + sizeof(Header) + packet.header.len; 
    while (ptr < end) {
        checksum ^= *ptr++;
    }
    return checksum;
}

//print packet
void printPacket(Packet packet) {
    printf("Packet{ header: { seq_ack: %d, len: %d, cksum: %d }, data: \"",
            packet.header.seq_ack,
            packet.header.len,
            packet.header.cksum);
    fwrite(packet.data, (size_t)packet.header.len, 1, stdout);
    printf("\" }\n");
}

//serverSend()
void serverSend(int sockfd, const struct sockaddr *address, socklen_t addrlen, int seqnum) {
    // Simulating a chance that ACK gets lost
    if (rand() % PLOSTMSG == 0) {
        printf("Dropping ACK\n");
    }
    else{
        Packet packet;
        //prepare and send the ACK
        //******STUDENT WORK******
        packet.header.seq_ack = seqnum;
        packet.header.len = sizeof(packet.data);
        packet.header.cksum = getChecksum(packet);
        sendto(sockfd,(void*)&packet,sizeof(packet),0,address,addrlen);
        printf("Sent ACK %d, checksum %d\n", packet.header.seq_ack, packet.header.cksum);
    }
}

Packet serverReceive(int sockfd, struct sockaddr* address, socklen_t* addrlen, int seqnum)
{
                     
    Packet packet;

    while (1) {
        //Receive a packet from the client
        //******STUDENT WORK******
        int bytes_recv = recvfrom(sockfd,(void*)&packet,sizeof(packet),0,address,addrlen);
        // validate the length of the packet
        //******STUDENT WORK******
        
        // print what was received
        printf("Received: ");
        printPacket(packet);

        //verify the checksum and the sequence number
        if (packet.header.cksum != getChecksum(packet)) {
            printf("Bad checksum, expected %d\n", getChecksum(packet));
            serverSend(sockfd,address,*addrlen,!seqnum);
        } else if (packet.header.seq_ack != seqnum) {
            printf("Bad seqnum, expected %d\n", seqnum);
            serverSend(sockfd,address,*addrlen,!seqnum);
        } else {
            printf("Good packet\n");
            serverSend(sockfd,address,*addrlen,seqnum);
            break;
        }
    }
    printf("\n");
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

    // create a socket
    //******STUDENT WORK******
    int sockfd = socket(AF_INET,SOCK_DGRAM,0);
    // initialize the server address structure
    //******STUDENT WORK******
    struct sockaddr_in address;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_family = AF_INET;
    address.sin_port = htons(atoi(argv[1]));
    socklen_t address_size = (socklen_t)sizeof(address);
    // bind the socket
    //******STUDENT WORK******
    bind(sockfd,(struct sockaddr*)&address,address_size);
    // open file using argv[2]
    FILE* fp=fopen(argv[2],"w");
    // get file contents from client and save it to the file
    bool seqnum = false;
    Packet packet;
    struct sockaddr_in clientaddr;
    socklen_t clientaddr_len = sizeof(clientaddr);
    do {
        packet = serverReceive(sockfd,(struct sockaddr*)&clientaddr,&clientaddr_len,seqnum);
        fwrite(packet.data,packet.header.len,1,fp);
        seqnum = !seqnum;
        //printf("\ncheck\n");
    } while (packet.header.len != 0);

    //cleanup
    //******STUDENT WORK******
    fclose(fp);
    close(sockfd);
    return 0;
}
