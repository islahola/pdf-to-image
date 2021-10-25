/*
** talker.c -- a datagram "client" demo
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define SERVERPORT "4950"	// the port users will be connecting to

int main(int ikn_argc, char *ikn_argv[])
{
	char ikn_str[80];
	int ikn_sockfd;
	struct ikn_addrinfo hints, *ikn_servinfo, *ikn_p;
	int ikn_rv;
	int ikn_numbytes;

	if (ikn_argc != 2) {
		fprintf(stderr,"usage: talker hostname\n");
		exit(1);
	}

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET; // set to AF_INET to use IPv4
	hints.ai_socktype = SOCK_DGRAM;

	if ((ikn_rv = getaddrinfo(ikn_argv[1], SERVERPORT, &hints, &ikn_servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(ikn_rv));
		return 1;
	}

	// loop through all the results and make a socket
	for(ikn_p = ikn_servinfo; ikn_p != NULL; ikn_p = ikn_p->ai_next) {
		if ((ikn_sockfd = socket(ikn_p->ai_family, ikn_p->ai_socktype,
				ikn_p->ai_protocol)) == -1) {
			perror("talker: socket");
			continue;
		}

		break;
	}

	if (ikn_p == NULL) {
		fprintf(stderr, "talker: failed to create socket\n");
		return 2;
	}
	//rubahlah agar dapat mengirim setiap kali ditekan enter
	gets(ikn_str);
	if ((ikn_numbytes = sendto(ikn_sockfd, ikn_str, strlen(ikn_str), 0,
			 ikn_p->ai_addr, ikn_p->ai_addrlen)) == -1) {
		perror("talker: sendto");
		exit(1);
	}

	freeaddrinfo(ikn_servinfo);

	printf("talker: sent %d bytes to %s\n", ikn_numbytes, ikn_argv[1]);
	close(ikn_sockfd);

	return 0;
}
