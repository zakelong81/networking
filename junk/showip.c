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
	int socket_type[3];
	char ipstr[INET6_ADDRSTRLEN];

	if (argc != 2) {
		fprintf(stderr, "usage: showip hostname\n");
		return 1;
	}

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC; // AF_INET or AF_INET6 to force version

	socket_type[1] = SOCK_STREAM;
	socket_type[2] = SOCK_DGRAM;
	socket_type[3] = SOCK_RAW;

	for (int i = 1; i < 4; i++)
	{
		hints.ai_socktype = socket_type[i];
		if ((status = getaddrinfo(argv[1], NULL, &hints, &res)) != 0) {
			fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
			return 2;
		}

		printf("IP addresses for %s:", argv[1]);

		for (p = res;p != NULL; p = p->ai_next) {
			void *addr;
			char *ipver;
			int socktype;
			// get the pointer to the address itself,
			// different fields in IPv4 and IPv6:
			if (p->ai_family == AF_INET) { // IPv4
				struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
				addr = &(ipv4->sin_addr);
				ipver = "IPv4";
				if (i == 1)
					printf("STREAM");
				if (i == 2)
					printf("DGRAM");
				if (i == 3)
					printf("RAW");
			}

			else { // IPv6
				struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
				addr = &(ipv6->sin6_addr);
				ipver = "IPv6";
				if (i == 1)
					printf("STREAM");
				if (i == 2)
					printf("DGRAM");
				if (i == 3)
					printf("RAW");
			}

			// convert the IP to a string and print it:
			inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
			printf("  %s: %s\n", ipver, ipstr);
		}

		freeaddrinfo(res); // free the linked list
	}
	return 0;
}
