/*
 * listerner.c -- a datagram sockets "server" demo
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

#define MYPORT "4950"
#define MAXBUFLEN 100

//get sockaddr, IPv4 or IPv6
void *get_in_addr(struct sockaddr *sa)
{
	if(sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in *)sa)->sin_addr);
	}
	return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

int main(void)
{
	int sockfd;
	struct addrinfo hints, *servinfo, *p;
	struct sockaddr_storage their_addr;
	socklen_t addr_len;
	char s[INET6_ADDRSTRLEN];
	char buf[MAXBUFLEN];
	int rv;
	int numbytes;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = AI_PASSIVE; // use my IP

	if(0 != (rv = getaddrinfo(NULL, MYPORT, &hints, &servinfo))) {
		fprintf(stderr, "getaddrinfo:%s\n", gai_strerror(rv));
		return 1;
	}

	//loop through all the results and bind to the first we can
	for(p = servinfo; p != NULL; p = p->ai_next) {
		if(-1 == (sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol))) {
			perror("listener: socket");
			continue;
		}

		if(-1 == (bind(sockfd, p->ai_addr, p->ai_addrlen))) {
			close(sockfd);
			perror("listener: bind");
			continue;

		}

		break;
	}	

	if(NULL == p) {
		fprintf(stderr, "listener: failed to bind\n");
		return 2;
	}
	
	freeaddrinfo(servinfo); // all done with this structure.

	printf("listener: waiting to recvfrom...\n");

	addr_len = sizeof(their_addr);
	if(-1 == (numbytes = recvfrom(sockfd, buf, MAXBUFLEN - 1, 0, (struct sockaddr *)&their_addr, &addr_len))) {
		perror("recvfrom");
		exit(1);
	}
	
	printf("listener: got packet from %s\n", inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *)&their_addr), s, sizeof(s)));
	printf("listener: packet is %d bytes long\n", numbytes);
	buf[numbytes] = '\0';
	printf("listener: packet contains \"%s\"\n", buf);

	close(sockfd);
	return 0;
}


