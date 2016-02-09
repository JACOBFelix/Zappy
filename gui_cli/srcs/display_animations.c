#include "display.h"

/*
** These functions display the non-basic animations (i.e those
** which have more than two frames).
*/
int		display_pony_bump(t_coord c, t_display *d, t_player *p)
{
  SDL_Rect	rect;
  SDL_Rect	coord;

  coord.x = (float)c.x / 1000;
  coord.y = (float)c.y / 1000;
  rect.x = (p->status_time > 1 && p->status_time < 5) ? (252) : (126);
  rect.y = (p->dir >= 3) ? (0) : (126);
  rect.w = 126;
  rect.h = 126;
  if (SDL_BlitSurface(d->ponies[p->lv - 1], &rect, d->w, &coord) != 0)
    {
      printf("Error: Could not display image: %s\n", SDL_GetError());
      return (-1);
    }
  return (0);
}

int		display_egg_opening(t_coord c, int loop,
				    SDL_Surface *dest, SDL_Surface *img)
{
  SDL_Rect	rect;
  SDL_Rect	coord;

  coord.x = (float)c.x / 1000;
  coord.y = (float)c.y / 1000;
  rect.x = ((loop % 40) / 10) * 126;
  rect.y = 0;
  rect.w = 126;
  rect.h = 126;
  if (SDL_BlitSurface(img, &rect, dest, &coord) != 0)
    {
      printf("Error: Could not display image: %s\n", SDL_GetError());
      return (-1);
    }
  return (0);
}

int		display_animation(t_coord c, SDL_Surface *src,
				  t_display *d)
{
  SDL_Rect	rect;
  SDL_Rect	coord;

  coord.x = (float)c.x / 1000;
  coord.y = (float)c.y / 1000;
  rect.x = ((d->loop % 20) / 10) * 126;
  rect.y = 0;
  rect.w = 126;
  rect.h = 126;
  if (SDL_BlitSurface(src, &rect, d->w, &coord) != 0)
    return (-1);
  return (0);
}
