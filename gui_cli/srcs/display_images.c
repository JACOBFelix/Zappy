#include "display.h"

static t_coord	g_walk_modifiers[] = {
  { 0, -15 },
  { 18, 0 },
  { 0, 15 },
  { -18, 0 }
};

/*
** This function draws the player whom data is passed
** as a parameter, depending on its level and status.
*/
int		display_pony(t_coord c, t_display *d, t_player *p)
{
  SDL_Rect	rect;
  SDL_Rect	coord;

  if (p->status == BUMPING)
    return (display_pony_bump(c, d, p));
  coord.x = (float)c.x / 1000;
  coord.y = (float)c.y / 1000;
  rect.x = 0 + p->status * 126;
  if (p->status == WALKING)
    {
      coord.x += g_walk_modifiers[p->dir - 1].x * p->status_time;
      coord.y += g_walk_modifiers[p->dir - 1].y * p->status_time;
      rect.x = 0;
    }
  rect.y = (p->dir >= 3) ? (0) : (126);
  rect.w = 126;
  rect.h = 126;
  if (p->status == INCANTATING && display_animation(c, d->fx_evo, d) == -1)
    return (-1);
  if (SDL_BlitSurface(d->ponies[p->lv - 1], &rect, d->w, &coord) != 0)
    {
      printf("Error: Could not display image: %s\n", SDL_GetError());
      return (-1);
    }
  return (0);
}

/*
** This function draws the image src on the surface dest
** on the coordinates c.
*/
int		display_image(t_coord c, SDL_Surface *src,
			      SDL_Surface *dest)
{
  SDL_Rect	coord;

  coord.x = (float)c.x / 1000;
  coord.y = (float)c.y / 1000;
  if (SDL_BlitSurface(src, NULL, dest, &coord) != 0)
    {
      printf("Error: Could not display image: %s\n", SDL_GetError());
      return (-1);
    }
  return (0);
}

int	display_loading_screen(t_display *d, int loaded)
{
  if (!loaded)
    SDL_BlitSurface(d->loading_screen, NULL, d->w, NULL);
  else
    SDL_BlitSurface(d->ls_end, NULL, d->w, NULL);
  if (strlen(SDL_GetError()) > 0)
    return (-1);
  if (SDL_Flip(d->w) == -1)
    return (-1);
  return (0);
}
