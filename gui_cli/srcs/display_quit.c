#include "display.h"

/*
** This function exits properly the display, freeing every
** SDL-allocated ressources.
*/
void	close_display(t_display *d)
{
  int	i;

  for (i = 0; i < 16; i++)
    SDL_FreeSurface(d->tiles[i]);
  i = 0;
  while (i < 7)
    {
      SDL_FreeSurface(d->rocks[i]);
      SDL_FreeSurface(d->ponies[i]);
      i++;
    }
  SDL_FreeSurface(d->ponies[i]);
  SDL_FreeSurface(d->loading_screen);
  SDL_FreeSurface(d->ls_end);
  SDL_FreeSurface(d->egg);
  SDL_FreeSurface(d->fx_evo);
  SDL_FreeSurface(d->fx_egg);
  SDL_FreeSurface(d->time_infos);
  SDL_CloseAudio();
  SDL_FreeWAV(d->wavbuff);
  SDL_Quit();
}
