/*
** Islah khofifah Nuraini
** 119091000097
** Listiner
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

#define MYPORT "4950"	// the port users will be connecting to

#define MAXBUFLEN 100

// get sockaddr, IPv4 or IPv6:
void *ikn_get_in_addr(struct ikn_sockaddr *sa)
{
	if (sa->sa_family == AF_INET) {
		return &(((struct ikn_sockaddr_in*)sa)->sin_addr);
	}

	return &(((struct ikn_sockaddr_in6*)sa)->sin6_addr);
}

int main(void)
{
	int ikn_sockfd;
	struct ikn_addrinfo hints, *ikn_servinfo, *ikn_p;
	int ikn_rv;
	int ikn_numbytes;
	struct ikn_sockaddr_storage their_addr;
	char ikn_buf[MAXBUFLEN];
	socklen_t ikn_addr_len;
	char ikn_s[INET6_ADDRSTRLEN];

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET; // set to AF_INET to use IPv4
	hints.ai_socktype = SOCK_DGRAM; //Datagram : Koneksi tanpa handshake
	hints.ai_flags = AI_PASSIVE; // use my IP

	if ((ikn_rv = getaddrinfo(NULL, MYPORT, &hints, &ikn_servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %ikn_s\n", gai_strerror(ikn_rv));
		return 1;
	}

	// loop through all the results and bind to the first we can
	for(ikn_p = ikn_servinfo; ikn_p != NULL; ikn_p = ikn_p->ai_next) {
		if ((ikn_sockfd = socket(ikn_p->ai_family, ikn_p->ai_socktype,
				ikn_p->ai_protocol)) == -1) {
			perror("listener: socket");
			continue;
		}

		if (bind(ikn_sockfd, ikn_p->ai_addr, ikn_p->ai_addrlen) == -1) {
			close(ikn_sockfd);
			perror("listener: bind");
			continue;
		}

		break;
	}

	if (ikn_p == NULL) {
		fprintf(stderr, "listener: failed to bind socket\n");
		return 2;
	}

	freeaddrinfo(ikn_servinfo);
	int c;
	printf("listener: waiting to recvfrom...\n");
	while(1){
		ikn_addr_len = sizeof their_addr;
		if ((ikn_numbytes = recvfrom(ikn_sockfd, ikn_buf, MAXBUFLEN-1 , 0,
			(struct ikn_sockaddr *)&their_addr, &ikn_addr_len)) == -1) {
			perror("recvfrom");
			exit(1);
			}

		printf("listener: got packet from %ikn_s\n",
			inet_ntop(their_addr.ss_family,
			ikn_get_in_addr((struct ikn_sockaddr *)&their_addr),
			ikn_s, sizeof ikn_s));
		printf("listener: packet is %d bytes long\n", ikn_numbytes);
		ikn_buf[ikn_numbytes] = '\0';
		printf("listener: packet contains \"%ikn_s\"\n", ikn_buf);
	}
	close(ikn_sockfd);

	return 0;
}
