/* Long Nguyen
 * Darin Croft
 * CSCI 446  Fall 2017 */
/* This code is an updated version of the sample code from "Computer Networks: A Systems
 * Approach," 5th Edition by Larry L. Peterson and Bruce S. Davis. Some code comes from
 * man pages, mostly getaddrinfo(3). */
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define SERVER_PORT "5432"
#define MAX_LINE 10000
#define MAX_PENDING 10000

int
main(int argc, char *argv[])
{
	struct addrinfo hints;
	struct addrinfo *rp, *result;
	char buf[MAX_LINE];
	int s, new_s;
	int len;

	int fd;

	/* Build address data structure */
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	hints.ai_protocol = 0;
	hints.ai_canonname = NULL;
	hints.ai_addr = NULL;
	hints.ai_next = NULL;

	/* Get local address info */
	if ((s = getaddrinfo(NULL, argv[1], &hints, &result)) != 0 )
	{
		fprintf(stderr, "%s: getaddrinfo: %s\n", argv[0], gai_strerror(s));
		exit(1);
	}

	/* Iterate through the address list and try to perform passive open */
	for (rp = result; rp != NULL; rp = rp->ai_next)
	{
		if ((s = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol)) == -1 )
		{
			continue;
		}

		if (!bind(s, rp->ai_addr, rp->ai_addrlen))
		{
			break;
		}

		close(s);
	}
	if (rp == NULL)
	{
		perror("stream-talk-server: bind");
		exit(1);
	}
	if (listen(s, MAX_PENDING) == -1)
	{
		perror("stream-talk-server: listen");
		close(s);
		exit(1);
	}
	freeaddrinfo(result);

	/* Wait for connection, then receive and print text */

	while(1)
	{
		new_s = accept(s, rp->ai_addr, &(rp->ai_addrlen));
		if (new_s < 0)
		{
			fprintf(stderr,"Server Unable to accept.\n");
			close(s);
			exit(3);
		}

		recv(new_s, buf, sizeof(buf), 0);


		fd = open(buf, O_RDONLY);
		if (fd < 0)
		{
			fprintf(stderr,"Can'not open file.\nFile doesn't exist on Server or couldn't request file.\n");
			exit (5);
		}
		else
			fprintf(stdout,"Open file success Server. \n");

		send(new_s, buf, strlen(buf), 0);
		recv(new_s, buf, sizeof(buf), 0);

		fprintf(stdout,"Reading and Writing please wait.\n");
		while ((len = read(fd, buf, sizeof(buf))) > 0)
		{
			if (send(new_s, buf, len, 0) == -1)
				break;
		}
		close(fd);
		close(new_s);
	}
	close(s);
	return 0;
}
