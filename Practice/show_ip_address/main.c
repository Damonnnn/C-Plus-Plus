/*
 * show IP address for a host given on the command line
 * Sample run:
		 	$ ./a.out www.baidu.com
			IP address for www.baidu.com:
 			IPv4:103.235.46.39

			$ ./a.out www.google.com
			IP address for www.google.com:
			IPv4:101.98.9.50
			IPv4:101.98.9.44
			IPv4:101.98.9.20
			IPv4:101.98.9.54
			IPv4:101.98.9.55
			IPv4:101.98.9.45
			IPv4:101.98.9.30
			IPv4:101.98.9.25
			IPv4:101.98.9.35
			IPv4:101.98.9.39
			IPv4:101.98.9.40
			IPv4:101.98.9.49
			IPv4:101.98.9.59
			IPv4:101.98.9.29
			IPv4:101.98.9.24
			IPv4:101.98.9.34
			IPv6:2a00:1450:4017:801::2004
* So, we can understand why the addrinfo is a linked list.

*/

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(int argc, char *argv[])
{
	struct addrinfo hints, *res, *p;
	int status;
	char ipstr[INET6_ADDRSTRLEN];

	if (argc != 2) {
		fprintf(stderr, "usage: showip hostname\n");
		return 1;
	}

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM; //TCP

	if ((status = getaddrinfo(argv[1], NULL, &hints, &res)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n",gai_strerror(status));
	return 2;
	}

	printf("IP address for %s:\n\n", argv[1]);
	
	for (p = res; p != NULL; p = p->ai_next) {
		void *addr;
		char * ipver;
		//get the pointer to the address itself,
		//different fields in IPv4 and IPv6
		if (p->ai_family == AF_INET) { //IPv4
			struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
			addr = &(ipv4->sin_addr);
			ipver = "IPv4";
		} else { //IPv6
			struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
			addr = &(ipv6->sin6_addr);
			ipver = "IPv6";
		}

		// convert the IP to a string and print it
		inet_ntop(p->ai_family, addr, ipstr, sizeof(ipstr));
		printf(" %s:%s\n",ipver, ipstr);
	}
	//free the linked list
	freeaddrinfo(res);
	return 0;

}
