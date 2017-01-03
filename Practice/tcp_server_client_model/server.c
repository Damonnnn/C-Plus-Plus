/*
 * server.c -- a stream socket server demo
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

#define PORT "3490" // the port will be connecting to
#define BACKLOG 10 // how many pending connections

void sigchld_handler(int s)
{
	// waitpid() might overwrite errno, so we save and restore it.
	int saved_errno = errno;
	while(waitpid(-1, NULL, WNOHANG) > 0);
	errno = saved_errno;

}

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
	int sockfd, new_fd;
	struct addrinfo hints, *servinfo, *p;
	struct sockaddr_storage their_addr;
	socklen_t sin_size;
	struct sigaction sa;
	int yes = 1;
	char s[INET6_ADDRSTRLEN];
	int rv;
	
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	if((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo:%s\n", gai_strerror(rv));
		return 1;
	}
	
	//loop through all the results and bind to the first we can
	for(p = servinfo; p != NULL; p = p->ai_next) {
		if(-1 == (sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol))) {
			perror("server: socket");
			continue;
		}

		if(-1 == (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)))) {
			perror("setsockopt");
			exit(1);
		}

		if(-1 == (bind(sockfd, p->ai_addr, p->ai_addrlen))) {
			close(sockfd);
			perror("server: bind");
			continue;

		}

		break;
	}	

	freeaddrinfo(servinfo); // all done with this structure.
	
	if(NULL == p) {
		fprintf(stderr, "server: failed to bind\n");
		exit(1);
	}	
	
	if(-1 == listen(sockfd, BACKLOG)) {
		perror("listen");
		exit(1);
	}
	
	sa.sa_handler = sigchld_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if(-1 == (sigaction(SIGCHLD, &sa, NULL))) {
		perror("sigaction");
		exit(-1);
	}

	printf("server: waiting for connections...\n");

	while(1) {
		sin_size = sizeof(their_addr);
		new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
		if(-1 == new_fd) {
			perror("accept");
			continue;
		}

		inet_ntop(their_addr.ss_family,
					get_in_addr((struct sockaddr *)&their_addr),
					s,
					sizeof(s));
		printf("server: got connection from %s\n", s);

		if(!fork()) {
			close(sockfd); // child doesn't need the listener.
			if(-1 == (send(new_fd, "Hello world! I am Damon", 23, 0))) {
				perror("send");
			}
			close(new_fd);
			exit(0);
		}
		close(new_fd); // parent doesn't need this
			
	}

	return 0;
}
