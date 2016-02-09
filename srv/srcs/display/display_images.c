#include "display.h"

int		display_pony(int x, int y, SDL_Surface *src, SDL_Surface *dest)
{
  SDL_Rect	rect;
  SDL_Rect	coord;

  coord.x = (float)x / 1000;
  coord.y = (float)y / 1000;
  rect.x = 0;
  rect.y = 0;
  rect.w = 126;
  rect.h = 126;
  if (SDL_BlitSurface(src, &rect, dest, &coord) != 0)
    return (-1);
  return (0);
}

int		display_image(int x, int y, SDL_Surface *src,
			      SDL_Surface *dest)
{
  SDL_Rect	coord;

  coord.x = (float)x / 1000;
  coord.y = (float)y / 1000;
  if (SDL_BlitSurface(src, NULL, dest, &coord) != 0)
    return (-1);
  return (0);
}
