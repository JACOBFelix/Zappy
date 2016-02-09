#include "commands.h"

int	get_tile_content(t_display *d, char **tab)
{
  int	x;
  int	y;
  int	i;

  if (!tab[1] || !tab[2])
    return (-1);
  x = atoi(tab[1]);
  y = atoi(tab[2]);
  i = 0;
  if (x >= d->map.width || y >= d->map.height
      || x < 0 || y < 0)
    return (-1);
  while (i < 7)
    {
      if (!tab[i + 3])
	return (-1);
      d->map.tiles[x + (y * d->map.width)].resources[i] = atoi(tab[i + 3]);
      i++;
    }
  return (0);
}
