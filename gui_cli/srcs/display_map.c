#include "display.h"

static t_coord	g_rocks_pos[] = {
  { -20000, -20000 },
  { -20000, 0 },
  { -30000, 20000 },
  { 0, -30000 },
  { 0, 20000 },
  { 20000, -20000 },
  { 20000, 0 },
  { 20000, 20000 }
};

int	display_players(t_display *d, t_coord coord, t_coord where)
{
  int	i;

  i = 0;
  while (i < 1000)
    {
      if (d->players[i].id != -1 && d->players[i].pos.x == coord.x
	  && d->players[i].pos.y == coord.y)
	if (display_pony(where, d, &d->players[i]) == -1)
	  return (-1);
      i++;
    }
  i = 0;
  while (i < 1000)
    {
      if (d->eggs[i].id != -1 && d->eggs[i].pos.x == coord.x
	  && d->players[i].pos.y == coord.y)
	if (display_image(where, d->egg, d->w) == -1)
	  return (-1);
      i++;
    }
  return (0);
}

int		draw_tile_content(t_display *d, t_coord coord, t_coord where)
{
  int		i;

  where.x += 15000;
  i = 0;
  while (i < 7)
    {
      if (d->map.tiles[coord.x + coord.y * d->map.width].resources[i] > 0)
	{
	  where.x += g_rocks_pos[i].x;
	  where.y += g_rocks_pos[i].y;
	  if (display_image(where, d->rocks[i], d->w) == -1)
	    return (-1);
	  where.x -= g_rocks_pos[i].x;
	  where.y -= g_rocks_pos[i].y;
	}
      i++;
    }
  where.x -= 15000;
  where.y -= 30000;
  return (display_players(d, coord, where));
}

/*
** This function draws the tile (x, y) of the map, and then
** everything that is on it.
** "actual" represents the coordinates of the tile which is displayed,
** whereas "tile" represents the coordinates of the tile on the screen.
*/
int		draw_tile(t_display *d, int x, int y, int objects)
{
  t_coord	tile;
  t_coord	actual;
  int		tmp;

  tmp = x + d->camera.x / 1000;
  actual.x = (tmp >= 0) ? (tmp % d->map.width) :
    ((tmp + d->map.width * (-tmp / d->map.width + 1)) % d->map.width);
  tmp = y + d->camera.y / 1000;
  actual.y = (tmp >= 0) ? (tmp % d->map.height) :
    ((tmp + d->map.height * (-tmp / d->map.height + 1)) % d->map.height);
  tile.x = (x * 1000 - d->camera.x % 1000) * 126;
  tile.y = (y * 1000 - d->camera.y % 1000) * 100;
  if (objects)
    return (draw_tile_content(d, actual, tile));
  else
    return (display_image(tile,
			  d->tiles[d->map.tiles[actual.x
						+ actual.y
						* d->map.width].water],
			  d->w));
}

/*
** This function displays every displayable tile on the screen.
** The screen is about 13 tiles wide and 11 tiles tall.
*/
int	display_map(t_display *d)
{
  int	i;
  int	j;

  if (d->map.height <= 0 || d->map.width <= 0)
    return (0);
  for (i = -1; i < 13; i++)
    for (j = -1; j < 11; j++)
      if (draw_tile(d, i, j, 0) == -1)
        return (-1);
  for (i = -1; i < 13; i++)
    for (j = -1; j < 11; j++)
      if (draw_tile(d, i, j, 1) == -1)
        return (-1);
  return (display_ui(d));
}
