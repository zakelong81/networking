/*
 * Darin Croft, Long Nguyen
 * CSCI 446
 * Fall 2017
 *
 * This template provides the framework you need for program 1. Complete the functions
 * defined and create any you feel are neccessary. stream-talk-client.c on Learn will
 * prove useful.
 */
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define SERVER_NAME "www.ecst.csuchico.edu"
#define SERVER_PORT "80"
#define REQUEST "GET /~kkredo/file.html HTTP/1.0\n\n"
#define SEARCH_TAG "<p>"

/*
 * Arguments: same as recv(2)
 * Return:-1 on error or bytes received
 *
 * Receive len bytes of data into array buf from socket sockfd. Always receive len bytes
 * of data unless the socket closes. The return value will fall into one of three cases:
 *   (1) on success the return value equals len
 *   (2) on error the return value equals -1
 *   (3) if the socket closes without receiving len bytes, then return the number
 *       actually received, which may be zero
 */
ssize_t recvx( int sockfd, void *buf, size_t len );

int main( int argc, char *argv[] ) {
	struct addrinfo hints, *res;
	int sockfd;
	int chunk = atoi(argv[1]);
	char buf[chunk];
	int count = 0;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	getaddrinfo(SERVER_NAME, SERVER_PORT, &hints, &res);

	sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

	int err = connect(sockfd, res->ai_addr, res->ai_addrlen);
	if(err == -1)
		printf("Connection failed.\n");

	err = send(sockfd, REQUEST, sizeof(REQUEST), 0);
	if(err == -1)
		printf("Send failed.\n");


	/* Call recvx in here ... */
	int size = recvx(sockfd, buf, chunk);
	while(size > 0){
		for(int i=0; i < size; i++){
			if(buf[i] == '<')
				if(buf[i+1] == 'p')
					if(buf[i+2] == '>')
						count++;
		}
		size = recvx(sockfd, buf, chunk);
	}

	close(sockfd);
	printf("Number of <p> tag:%i\n",count);

	return 0;
}

ssize_t recvx( int sockfd, void *buf, size_t len ) {
	char *buffer;
	int bytesread, size;

	buffer = buf;
	size = 0;
	while(size < len){
		bytesread = recv(sockfd, buffer+size, len-size, 0);
		if(bytesread <= 0){
			if(size == 0){
				return bytesread;
			}
			break;
		}
		size += bytesread;
	}
	return size;

	/*
	 * Define recvx to return exactly len bytes unless an error occurs or the socket
	 * closes.
	 */
}
