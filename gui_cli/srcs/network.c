#include <unistd.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include "display.h"

int			network_init(char const *const ip,
				     char const *const port,
				     t_network *const net)
{
  int			err;
  struct addrinfo	hints;
  struct addrinfo	*a;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  if ((err = getaddrinfo(ip, port, &hints, &a)))
    return (fprintf(stderr, "Getaddrinfo: %s\n", gai_strerror(err)) * 0 - 1);
  if ((net->fd = socket(a->ai_family, a->ai_socktype, a->ai_protocol)) == -1)
    {
      perror("socket");
      return (-1);
    }
  if (connect(net->fd, a->ai_addr, a->ai_addrlen) == -1)
    {
      close(net->fd);
      perror("connect");
      return (-1);
    }
  freeaddrinfo(a);
  net->pollfds->fd = net->fd;
  net->pollfds->events = POLLIN;
  write(net->fd, "GRAPHIC\n", sizeof("GRAPHIC\n") - 1);
  return (net->fd);
}

void	network_close(t_network *const network) {
  close(network->fd);
}
