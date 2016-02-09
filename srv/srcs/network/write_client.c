#include <stdlib.h>
#include "server.h"
#include "network.h"

static void	write_buf_to_client(t_player *client)
{
  t_network_buf	*buf;
  void		*ptr;
  ssize_t	ssize;

  buf = (t_network_buf *)client->list_buffer_out->data;
  if (buf)
    {
      if (buf->buffer == NULL)
	{
	  write(client->fd, CMD_KO, sizeof(CMD_KO));
	  list_pop_front(&(client->list_buffer_out));
	  return ;
	}
      ptr = buf->buffer + (size_t)buf->ptr;
      ssize = write(client->fd, ptr, buf->size - (size_t)buf->ptr);
      if (ssize > 0)
	{
	  buf->ptr += ssize;
	  if ((size_t)buf->ptr >= buf->size)
	    {
	      free(buf->buffer);
	      list_pop_front(&(client->list_buffer_out));
	    }
	}
    }
}

void		write_client(t_player *client)
{
  if (client->list_buffer_out == NULL)
    debug_msgf("ERROR: Try to send an empty buffer");
  else
    {
      write_buf_to_client(client);
    }
}
