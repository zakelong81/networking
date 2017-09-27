#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>

#define BUF_SIZE 8192
int main(int argc, char* argv[]) {

    int input_fd, output_fd;    /* Input and output file descriptors */
    ssize_t ret_in;    /* Number of bytes returned by read() and write() */
    char buffer[BUF_SIZE];      /* Character buffer */
    char lower_to_upper[BUF_SIZE];


    /* open a file*/
    if (argv [1] == NULL)
        input_fd = open (some_file, O_RDONLY);
    else
        input_fd = open (argv [1], O_RDONLY);
    /* Create output file descriptor */
    if (argv [2] == NULL)
        output_fd = open("some_file.up", O_WRONLY | O_CREAT, 0644);
    else
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
}
