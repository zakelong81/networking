/*
 * A function that randomly drops a packet. packetErrorSend has the same
 * format and arguments as send(2). Packets are capped at
 * MAX_PACKET_DATA_SIZE bytes.
 *
 * When packetErrorSend drops a packet, it will return len, up to a max
 * of MAX_PACKET_DATA_SIZE, as if the packet was actually sent.
 *
 */
#include <sys/types.h>
#include <sys/socket.h>

#define MAX_PACKET_DATA_SIZE (1400)

ssize_t packetErrorSend(int sockfd, const void *buf, size_t len, int flags);
