/*
 * talker.c -- a datagram sockets "client" demo
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

#define SERVERPORT "4950"

int main(int argc, char *argv[])
{
	int sockfd;
	struct addrinfo hints, *servinfo, *p;
	int rv;
	int numbytes;
	
	if(argc != 3) {
		fprintf(stderr, "usage: talker hostname message\n");
		exit(1);
	}	

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;

	if(0 != (rv = getaddrinfo(argv[1], SERVERPORT, &hints, &servinfo))) {
		fprintf(stderr, "getaddrinfo:%s\n", gai_strerror(rv));
		return 1;
	}

	//loop through all the results and bind to the first we can
	for(p = servinfo; p != NULL; p = p->ai_next) {
		if(-1 == (sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol))) {
			perror("talker: socket");
			continue;
		}

		break;
	}	

	if(NULL == p) {
		fprintf(stderr, "talker: failed to create socket\n");
		return 2;
	}

	if(-1 == (numbytes = sendto(sockfd, argv[2], strlen(argv[2]), 0, p->ai_addr, p->ai_addrlen))) {
		perror("talker: sendto");
		exit(1);
	}

	freeaddrinfo(servinfo);
	printf("talker: send %d bytes to %s\n", numbytes, argv[1]);
	close(sockfd);

	return 0;
}




