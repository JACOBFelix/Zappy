#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include "display.h"

void	update_ponies(t_display *d)
{
  int	i;

  i = 0;
  while (i < 1000)
    {
      if (d->players[i].id != -1)
	{
	  d->players[i].status_time++;
	  if (d->players[i].status_time >= 7
	      && d->players[i].status != INCANTATING
	      && d->players[i].status != DEAD)
	    {
	      if (d->players[i].status == WALKING)
		{
		  d->players[i].pos.x = d->players[i].new_pos.x;
		  d->players[i].pos.y = d->players[i].new_pos.y;
		}
	      d->players[i].status = IDLE;
	      d->players[i].status_time = 0;
	    }
	}
      i++;
    }
}

/*
** returned buffer has to be freed
*/
static char	*read_all(t_network *const network)
{
  ssize_t	len;
  char		buff[512];
  char		*full_buf;
  char		*old_buf;

  full_buf = NULL;
  while ((len = read(network->fd, buff, sizeof(buff) - 1)) > 0)
    {
      buff[len] = 0;
      old_buf = full_buf;
      if (asprintf(&full_buf, "%s%s", full_buf ? full_buf : "", buff) == -1)
	{
	  perror("asprintf");
	  return (NULL);
	}
      free(old_buf);
      if (len != sizeof(buff) - 1)
	break ;
    }
  return (full_buf);
}

static int	get_data(t_display *const d, t_network *const network)
{
  int		i;
  int		retpoll;
  char		*buf;
  char		**lines;

  if ((retpoll = poll(network->pollfds, 1, 20)) == -1)
    {
      perror("poll");
      return (-1);
    }
  else if (retpoll
	   && network->pollfds->revents & POLLIN)
    {
      if (!(buf = read_all(network))
	  || !(lines = str_to_wordtab(buf, "\n")))
	return (-1);
      i = -1;
      while (lines[++i])
	parse_command(d, lines[i]);
      free(buf);
    }
  return (retpoll);
}

/*
** This is the display loop.
** As long as it doesn't receive an exit command, it reads the server inputs,
** then looks at the events and displays the map.
*/
static int	server_loop(t_display *d, t_network *const network)
{
  Uint32	last_t;
  Uint32	last_turn_t;

  last_t = SDL_GetTicks();
  last_turn_t = SDL_GetTicks();
  while (d->quit == 0)
    {
      if (get_data(d, network) == -1)
	return (0);
      keyboard_events(d, SDL_GetTicks() - last_t, network->fd);
      last_t = SDL_GetTicks();
      SDL_FillRect(d->w, NULL, 0x00);
      if (display_map(d))
	return (-1);
      if (SDL_Flip(d->w) == -1)
        return (-1);
      update_ponies(d);
      while (SDL_GetTicks() > last_turn_t + d->time)
	{
	  d->loop++;
	  last_turn_t += d->time;
	}
    }
  return (0);
}

int		main(int ac, char **av)
{
  t_display	d;
  t_network	network;
  int		fd;
  time_t	t;

  srand((unsigned) time(&t));
  if (parse_arguments(ac, av, &fd, &network) == -1)
    return (1);
  if (init_display(&d) == -1)
    {
      printf("Something went wrong while loading: %s\n", SDL_GetError());
      return (1);
    }
  SDL_Delay(500);
  if (server_loop(&d, &network))
    {
      if (strlen(SDL_GetError()) > 0)
	printf("Something went wrong: %s\n", SDL_GetError());
      else
	printf("Fatal error: malloc failed\n");
      return (1);
    }
  close_display(&d);
  network_close(&network);
  return (0);
}
