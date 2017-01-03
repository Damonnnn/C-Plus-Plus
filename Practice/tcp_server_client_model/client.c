/*
 * client.c -- a stream socket client demo
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

#define PORT "3490" // the port clinet will be connecting to
#define MAXDATASIZE 100 // max number of bytes we can et at once

//get sockaddr, IPv4 or IPv6
void *get_in_addr(struct sockaddr *sa)
{
	if(sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in *)sa)->sin_addr);
	}
	return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

int main(int argc, char *argv[])
{
	int sockfd, numbytes;
	char buf[MAXDATASIZE];
	struct addrinfo hints, *servinfo, *p;
	int rv;
	char s[INET6_ADDRSTRLEN];

	if(2 != argc) {
		fprintf(stderr, "usage: client hostname\n");
		exit(1);
	}

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if(0 != (rv = getaddrinfo(argv[1], PORT, &hints, &servinfo))) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
	}
	
	//loop through all the results and bind to the first we can
	for(p = servinfo; p != NULL; p = p->ai_next) {
		if(-1 == (sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol))) {
			perror("client: socket");
			continue;
		}


		if(-1 == (connect(sockfd, p->ai_addr, p->ai_addrlen))) {
			close(sockfd);
			perror("client: connect");
			continue;

		}

		break;
	}
	
	if(NULL == p) {
		fprintf(stderr, "client: failed to connect\n");
		return 2;
	}	

	inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr), s, sizeof(s));
	printf("client: connecting to %s\n", s);
	freeaddrinfo(servinfo); // all done with this structure
	if(-1 == (numbytes = recv(sockfd, buf, MAXDATASIZE - 1, 0))) {
		perror("recv");
		exit(1);
	}
	buf[numbytes] = '\0';
	printf("client: received '%s' \n", buf);
	
	close(sockfd);

	return 0;
}

