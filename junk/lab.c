#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <ifaddrs.h>
#include <netinet/ether.h>
#include <net/ethernet.h>
#include <linux/if_packet.h>

int main()
{
  int status;
  void *addr;
  struct ifaddrs hints, *res, *p;
  struct ifaddrs *ifa;

  char *IF, *AF;
  char ipstr[INET6_ADDRSTRLEN];


    if ((status = getifaddrs(&ifa)) != 0)
    {
      fprintf(stderr, "getifaddrs: %s\n", gai_strerror(status));
      return 2;
    }

    for (p = ifa; p != NULL; p = p->ifa_next)
    {
      IF = p->ifa_name ;
		    if(p->ifa_addr->sa_family == AF_PACKET && ifa -> ifa_data != NULL)
        {
          AF = "AF_PACKET";

          char* nl = "NULL";
          struct sockaddr_ll *eadder = (struct sockaddr_ll *)p->ifa_addr;
          printf("%s %s %s\n", IF, AF, ether_ntoa(( const struct ether_addr*)eadder->sll_addr));

          if (p->ifa_addr->sa_family == AF_INET)
          {
            AF = "AF_INET";
          }
          if (p->ifa_addr->sa_family == AF_INET6)
          {
            AF = "AF_INET6";
          }

          struct sockaddr_in *ip = (struct sockaddr_in *)p->ifa_addr;
          addr = &(ip->sin_addr);

          if(AF != "AF_PACKET")
          {
            inet_ntop(p->ifa_addr -> sa_family, addr, ipstr, sizeof ipstr);
      			printf("%s %s %s\n", IF , AF, ipstr);
          }
        }
    }
}
