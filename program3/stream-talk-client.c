/* Long Nguyen
 * Darin Croft
 * CSCI 446  Fall 2017 */
/* This code is an updated version of the sample code from "Computer Networks: A Systems
 * Approach," 5th Edition by Larry L. Peterson and Bruce S. Davis. Some code comes from
 * man pages, mostly getaddrinfo(3). */
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "packetErrorSend.h"


#define SERVER_PORT "5432"
#define MAX_LINE 10000

int
main(int argc, char *argv[])
{
	struct addrinfo hints;
	struct addrinfo *rp, *result;
	char *host;
	char file[MAX_LINE];
	int s;
	int len;

	int fd;
	char *filename;

	/***/

	/***/


	if (argc==4)
	{
		host = argv[1];
		filename = argv[3];
	}
	else
	{
		fprintf(stderr, "usage: %s host\n", argv[0]);
		exit(1);
	}

	/* Translate host name into peer's IP address */
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = 0;
	hints.ai_protocol = 0;

	if ((s = getaddrinfo(host, argv[2], &hints, &result)) != 0 )
	{
		fprintf(stderr, "%s: getaddrinfo: %s\n", argv[0], gai_strerror(s));
		exit(1);
	}

	/* Iterate through the address list and try to connect */
	for (rp = result; rp != NULL; rp = rp->ai_next)
	{
		if ((s = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol)) == -1 )
		{
			continue;
		}

		if (connect(s, rp->ai_addr, rp->ai_addrlen) != -1)
		{
			break;
		}

		close(s);
	}
	if (rp == NULL)
	{
		perror("stream-talk-client: connect");
		exit(1);
	}
	freeaddrinfo(result);


	/* Main loop: get and send lines of text */
	packetErrorSend(s, filename, strlen(filename), 0);
	recv(s, file, sizeof(file), 0);
	fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, S_IWUSR | S_IRUSR);


	packetErrorSend(s, file, strlen(file), 0);

	while ((len = recv(s, file, sizeof(file), 0)) > 0)
	{
		if (write(fd, file, len) == -1)
		{
			fprintf(stderr,"Unable to write. \n");
			close(fd);			close(s);
			exit(2);
		}
	}
	shutdown(s, SHUT_RDWR);
	close(fd);
	close(s);
	return 0;
}
