#include <string.h>
#include "network.h"

static int		get_local_ip(t_server *server)
{
  struct sockaddr_in	name;
  struct sockaddr_in	serv;
  socklen_t		size;
  char			buffer[256];
  int			fd;

  size = sizeof(name);
  if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    return (-1);
  memset(&serv, 0, sizeof(serv));
  serv.sin_family = AF_INET;
  serv.sin_addr.s_addr = inet_addr(ADDR_LOCAL_IP);
  serv.sin_port = htons(PORT_LOCAL_IP);
  if (connect(fd, (const struct sockaddr*)&serv, sizeof(serv)) == -1)
    return (-1);
  if (getsockname(fd, (struct sockaddr*)&name, &size) == -1)
    return (-1);
  server->network.local_ip = strdup(inet_ntop(AF_INET, &name.sin_addr,
					      buffer, 256));
  close(fd);
  return (0);
}

int			init_network(t_server *server)
{
  struct sockaddr_in	server_addr;
  int			unused;

  unused = 1;
  if ((server->network.fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    return (derror("error: socket"));
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(server->nb_port);
  if (setsockopt(server->network.fd, SOL_SOCKET, SO_REUSEADDR,
		 &unused, sizeof(int)) == -1)
    return (derror("error: setsockopt"));
  if ((bind(server->network.fd, (struct sockaddr*)&server_addr,
	    sizeof((server_addr)))) == -1)
    return (derror("error: bind"));
  if ((listen(server->network.fd, CLIENTS_MAX)) == -1)
    return (derror("error: listen"));
  get_local_ip(server);
  if (!server->network.local_ip)
    server->network.local_ip = strdup("0.0.0.0");
  server->network.alive = 1;
  debug_msgf("Server IP: %s", server->network.local_ip);
  debug_msgf("Server is listening on port %d", server->nb_port);
  return (0);
}
