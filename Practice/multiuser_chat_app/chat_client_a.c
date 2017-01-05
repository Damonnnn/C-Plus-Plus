/*
** selectserver.c -- a cheezy multiperson chat server
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>


#define PORT "9034" // port we're going to connect to
#define MAXDATASIZE (100) // the maximum message size
// get sockaddr, IPv4 or IPv6:
/*
void *get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}
	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}
*/

int main(int argc, char *argv[])
{
	struct addrinfo hints, *res, *p;
	int status;
	int fd;
	int i;
	pid_t fpid;
	char buf[MAXDATASIZE];
	int numbytes;
	//fd_set master;
	
	if(2 > argc) {
		printf("usage: please input the ip address you want to connect.\n");
		return 1;
	}

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	//hints.ai_flags = AI_PASSIVE; we need to indentify the address ourselves.
	if(0 != (status = getaddrinfo(argv[1], PORT, &hints, &res))) {
		fprintf(stderr, "selectserver: %s\n", gai_strerror(status));
		exit(1);
	}

	// get a file descriptor
	for(p = res; NULL != p ; p = p->ai_next) {
		if(-1 == (fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol))) { // try to get a file descriptor
			perror("socket error.");
			continue;
		}

		if(-1 == (connect(fd, p->ai_addr, p->ai_addrlen))) { // we start a connect initiatively
			close(fd);
			perror("connect error.");
			continue;
		}
		break;
	}
	if(NULL == p) {
		perror("Failed to connect.");
		exit(1);
	}
	freeaddrinfo(res);

	
	//send and receive
	//we will creat 2 threads, one for sending, one for recieving
	//we don't use select() function here for it is not suitable.
	if(0 > (fpid = fork())) {
		perror("fork error");
		exit(1);
	}

	if(0 == fpid) { //parent thread goes here. we receive message here.
		while(1) {
			
			if(-1 == (numbytes = recv(fd, buf, MAXDATASIZE, 0))) {
				perror("recieve..");
				exit(1);
			}
			printf("%s",buf);
		}
	} else { // child thread goes here. we send message here
		buf[0] = 'a';
		buf[1] = ':';
		while(1) {
			fgets(buf+2, MAXDATASIZE-2, stdin);
			if(-1 == (send(fd, buf, sizeof(buf), 0))) {
				perror("send..");
				exit(1);
			}
		}
	}
	
	
	
	return 0;
}
