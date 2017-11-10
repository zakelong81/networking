#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <netinet/ether.h>
#include <ifaddrs.h>
#include <net/ethernet.h>
#include <linux/if_packet.h>

int main()
{
  int status;
  char ipstr[INET6_ADDRSTRLEN];

  struct ifaddrs *ifaddr, *p;
  char *AF_FAMILY;

    if ((status = getifaddrs(&ifaddr)) != 0)
    {
      fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
      return 2;
    }

    for (p = ifaddr; p != NULL; p = p->ifa_next)
    {
		    if(p->ifa_addr->sa_family == AF_PACKET && ifaddr -> ifa_data != NULL)
        {
          AF_FAMILY = "AF_PACKET";
          struct sockaddr_ll *eadder = (struct sockaddr_ll *)p->ifa_addr;
          printf("%s %s %s\n", p->ifa_name, "AF_PACKET", ether_ntoa(( const struct ether_addr*)eadder->sll_addr));

          if (p->ifa_addr->sa_family == AF_INET)
          {
            AF_FAMILY = "AF_INET";
          }
          if (p->ifa_addr->sa_family == AF_INET6)
          {
            AF_FAMILY = "AF_INET6";
          }

          struct sockaddr_in *ip = (struct sockaddr_in *)p->ifa_addr;
          void *addr = &(ip->sin_addr);

          if(AF_FAMILY!= "AF_PACKET")
          {
            inet_ntop(p->ifa_addr -> sa_family, addr, ipstr, sizeof ipstr);
      			printf("%s %s %s\n", p->ifa_name , AF_FAMILY, ipstr);
          }
        }
    }
}
