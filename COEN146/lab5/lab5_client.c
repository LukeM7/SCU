//Luke Manzitto
//02/08/2021
//Lab5 Client
//Client side of a UDP
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


//clientSend()
void clientSend(int sockfd, const struct sockaddr *address, socklen_t addrlen, Packet packet) {
    while (1) {
		if(rand()%20 > 4){
			packet.header.cksum=rand() % 10000000 + 100000;
		}
		else packet.header.cksum=getChecksum(packet);
        // send the packet
        printf("Client: sending packet\n");
		//******STUDENT WORK******
        sendto(sockfd,(void*)&packet,sizeof(packet),0,address,addrlen);
        // receive an ACK from the server
        Packet recvpacket;
		//******STUDENT WORK******
        recvfrom(sockfd,(void*)&recvpacket,sizeof(recvpacket),0,(struct sockaddr*)address,&addrlen);
        // log what was received
        printf("Received ACK %d, checksum %d - ", recvpacket.header.seq_ack, recvpacket.header.cksum);

        //print received packet
        //******STUDENT WORK****** 

        // validate the ACK
        if(recvpacket.header.cksum != getChecksum(recvpacket)) {
            // bad checksum, resend packet
            printf("Bad checksum, expected checksum was: %d\n", packet.header.cksum);
        } else if (	recvpacket.header.seq_ack != packet.header.seq_ack) {
            // incorrect sequence number, resend packet
            printf("Bad seqnum, expected sequence number was: %d\n", packet.header.seq_ack);
        } else {
            // good ACK, we're done
            printf("Good ACK\n");
            break;
        }
    }
}

int main(int argc, char *argv[]) {
    // check arguments
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <ip> <port> <infile>\n", argv[0]);
        return 1;
    }

    // seed the RNG
    srand((unsigned)time(NULL));

    // create and configure the socket [name the socket sockfd] 
	//******STUDENT WORK******	    
    int sockfd = socket(AF_INET,SOCK_DGRAM,0);

    // initialize the server address structure using argv[2] and argv[1]
    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_addr.s_addr = inet_addr(argv[1]);
    address.sin_family = AF_INET;
    address.sin_port = htons(atoi(argv[2]));
	//******STUDENT WORK******
    FILE *fp = fopen(argv[3],"r");
    // open file using argv[3]
	//******STUDENT WORK******

    // send file contents to server
	//-create a packet
	//-set the seq_ack field 
	//-set the len field
	//-calculate the checksum
	//-send the packet
	//******STUDENT WORK******
    socklen_t address_size = (socklen_t)sizeof(address);
    int writer = 0;
    bool seq = false;
    Packet packet;
    while(writer = fread(packet.data,1,sizeof(packet.data),fp)){
        packet.header.seq_ack = seq;
        packet.header.len = writer;
        packet.header.cksum = getChecksum(packet);
        clientSend(sockfd,(struct sockaddr*)&address,address_size,packet);
        seq = !seq;
    }


    // send zero-length packet to server to end connection
	//******STUDENT WORK******
    Packet endPacket;
    endPacket.header.len = 0;
    endPacket.header.cksum = getChecksum(endPacket);
    endPacket.header.seq_ack = seq;
    clientSend(sockfd,(struct sockaddr*)&address,address_size,endPacket);
    // clean up
	//-close the sockets and file
    	//******STUDENT WORK******
    fclose(fp);
    close(sockfd);
    return 0;
}
