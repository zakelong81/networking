#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>


#define BUF_SIZE 8192
#define SERVER_NAME "farnsworth.ecst.csuchico.edu"
#define SERVER_PORT "80"
#define REQUEST "GET /lab_docs/reset_instructions.pdf HTTP/1.0\r\n\r\n"


int main(int argc, char* argv[]) {

    int input_fd, output_fd;    /* Input and output file descriptors */
    ssize_t ret_in;    /* Number of bytes returned by read() and write() */
    char buffer[BUF_SIZE];      /* Character buffer */
    char lower_to_upper[BUF_SIZE];

    // struct addrinfo hints, *res;
    // int sockfd;
    // int chunk = atoi(argv[1]);
    // char *message , server_reply[6000];

    // memset(&hints, 0, sizeof hints);
    // hints.ai_family = AF_UNSPEC;
    // hints.ai_socktype = SOCK_STREAM;
    //
    // getaddrinfo(SERVER_NAME, SERVER_PORT, &hints, &res);
    //
    // sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    //
    // connect(sockfd, res->ai_addr, res->ai_addrlen);
    // send(sockfd, REQUEST, sizeof(REQUEST), 0);
    //
    // recv(sockfd, server_reply , 6000 , 0);
    // puts("Reply received\n");
    // puts(server_reply);

    /* open a file*/
    if (argv [1] == NULL)
        input_fd = open ("some_file", O_RDONLY);
    else if (argv [1] != NULL)
        input_fd = open (argv [1], O_RDONLY);

    /* Create output file descriptor */
    if (argv [2] == NULL)
        output_fd = open("some_file.up", O_WRONLY | O_CREAT, 0644);
    else if (argv [2] != NULL)
        output_fd = open(argv [2], O_WRONLY | O_CREAT, 0644);

    /* Copy process */
    while((ret_in = read (input_fd, &buffer, BUF_SIZE)) > 0)
    {
      printf ("%zu\n", ret_in); // printout the packet size in bytes
      for (int i = 0 ; buffer[i]; i ++)
        lower_to_upper[i] = toupper(buffer[i]);
      write (output_fd, &lower_to_upper, (ssize_t) ret_in);
    }

    /* Close file descriptors */
    close (input_fd);
    close (output_fd);

    return (EXIT_SUCCESS);
    // return 0;
}
