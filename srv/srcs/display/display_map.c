#include "display.h"

static t_coordinates	g_rocks_pos[] = {
  { -200, -200 },
  { -200, 0 },
  { -200, 200 },
  { 0, -200 },
  { 0, 200 },
  { 200, -200 },
  { 200, 0 },
  { 200, 200 }
};

int	display_players(t_display *d, t_list *curr,
			t_coordinates actual, t_coordinates tile)
{
  if (!curr)
    return (0);
  if (((t_player*)curr->data)->pos.x == actual.x
      && ((t_player*)curr->data)->pos.y == actual.y)
    {
      if (((t_player*)curr->data)->level > 0 &&
	  ((t_player*)curr->data)->state == PLAYER_IS_READY &&
	  display_pony(tile.x * 126, tile.y * 100,
		       d->ponies[((t_player*)curr->data)->level - 1],
		       d->w) == -1)
	return (-1);
    }
  return (display_players(d, curr->next, actual, tile));
}

int	display_eggs(t_display *d, t_list *curr,
		     t_coordinates actual, t_coordinates tile)
{
  if (!curr)
    return (0);
  if (((t_egg*)curr->data)->pos.x == actual.x
      && ((t_egg*)curr->data)->pos.y == actual.y)
    {
      if (display_image(tile.x * 126, tile.y * 100 - 30000,
			d->egg, d->w) == -1)
	return (-1);
    }
  return (display_eggs(d, curr->next, actual, tile));
}

int	draw_tile_content(t_display *d, t_server *s,
			  t_coordinates actual, t_coordinates tile)
{
  t_map	map;
  int	i;

  tile.x += 150;
  map = s->map[actual.x + actual.y * s->world_width];
  for (i = 0; i < 8; i++)
    {
      if (map.item[i] > 0)
	{
    tile.x += g_rocks_pos[i].x;
    tile.y += g_rocks_pos[i].y;
	  if (display_image(tile.x * 126, tile.y * 100 - 15000,
			    d->rocks[i], d->w) == -1)
	    return (-1);
    tile.x -= g_rocks_pos[i].x;
    tile.y -= g_rocks_pos[i].y;
	}
    }
  return (0);
}

int		draw_tile(t_display *d, t_server *s, int x, int y)
{
  t_coordinates	tile;
  t_coordinates	actual;
  int		tmp;

  tmp = x + d->camera_x / 1000;
  actual.x = (tmp >= 0) ? (tmp % s->world_width) :
    ((tmp + s->world_width * (-tmp / s->world_width + 1)) % s->world_width);
  tmp = y + d->camera_y / 1000;
  actual.y = (tmp >= 0) ? (tmp % s->world_height) :
    ((tmp + s->world_height * (-tmp / s->world_height + 1))
     % s->world_height);
  tile.x = x * 1000 - d->camera_x % 1000;
  tile.y = y * 1000 - d->camera_y % 1000;
  if (display_image(tile.x * 126, tile.y * 100, d->tile, d->w) == -1)
    return (-1);
  if (draw_tile_content(d, s, actual, tile) == -1)
    return (-1);
  if (display_eggs(d, s->egg_list, actual, tile) == -1)
    return (-1);
  if (display_players(d, s->network.client, actual, tile) == -1)
    return (-1);
  return (0);
}

int	display_map(t_display *d, t_server *s)
{
  int	i;
  int	j;

  i = -1;
  while (i < 13)
    {
      j = -1;
      while (j < 11)
	{
	  if (draw_tile(d, s, i, j) == -1)
	    return (-1);
	  j++;
	}
      i++;
    }
  return (0);
}
