#include "commands.h"

static t_tile	g_rivers_no[] = {
  { { 0, 0 }, { 0, 0, 0, 0, 0, 0, 0 }, 1 },
  { { 1, 0 }, { 0, 0, 0, 0, 0, 0, 0 }, 2 },
  { { 1, 1 }, { 0, 0, 0, 0, 0, 0, 0 }, 4 },
  { { 0, 1 }, { 0, 0, 0, 0, 0, 0, 0 }, 8 }
};

static t_coord	g_dirs[] = {
  { 0, -1 },
  { 1, 0 },
  { 0, 1 },
  { -1, 0 }
};

void	init_tile(t_display *d, int n, int i, int j)
{
  d->map.tiles[n].coords.x = i;
  d->map.tiles[n].coords.y = j;
  i = 0;
  while (i < 7)
    {
      d->map.tiles[n].resources[i] = 0;
      i++;
    }
}

void	rivers_to_tiles(t_display *d, char *rivers)
{
  int	i;
  int	j;
  int	n;
  int	w;
  int	h;

  w = d->map.width;
  h = d->map.height;
  for (i = 0; i < w; i++)
    {
      for (j = 0; j < h; j++)
	{
	  d->map.tiles[i + j * w].water = 0;
	  for (n = 0; n < 4; n++)
	    {
	      if (rivers[(i + g_rivers_no[n].coords.x) % w
			 + (j + g_rivers_no[n].coords.y) % h * w] == 1)
		d->map.tiles[i + j * w].water += g_rivers_no[n].water;
	    }
	}
    }
}

void		generate_rivers(t_display *d)
{
  char		rivers[d->map.width * d->map.height];
  int		i;
  int		max;
  int		r;
  int		dir;
  t_coord	start;

  start.x = rand() % d->map.width;
  start.y = rand() % d->map.height;
  dir = rand() % 4;
  max = d->map.width + d->map.height;
  for (i = 0; i < d->map.width * d->map.height; i++)
    rivers[i] = 0;
  for (i = 0; i < max; i++)
    {
      rivers[start.x + start.y * d->map.width] = 1;
      start.x = (start.x + g_dirs[dir].x + d->map.width) % d->map.width;
      start.y = (start.y + g_dirs[dir].y + d->map.height) % d->map.height;
      r = rand() % 8;
      if (r == 0)
	dir = (dir + 1) % 4;
      else if (r == 1)
	dir = (dir + 3) % 4;
    }
  rivers_to_tiles(d, rivers);
}

int	set_map_size(t_display *d, char **tab)
{
  int	i;
  int	j;

  if (!tab[1] || !tab[2])
    return (-1);
  d->map.width = atoi(tab[1]);
  d->map.height = atoi(tab[2]);
  d->map.nb_tiles = d->map.width * d->map.height;
  d->map.tiles = malloc(sizeof(t_tile) * d->map.nb_tiles);
  if (d->map.tiles == NULL)
    return (-1);
  for (i = 0; i < d->map.width; i++)
    for (j = 0; j < d->map.height; j++)
      init_tile(d, i + (j * d->map.width), i, j);
  generate_rivers(d);
  return (0);
}

int	set_game_time(t_display *d, char **tab)
{
  if (!tab[1])
    return (-1);
  d->time = atoi(tab[1]);
  return (0);
}
