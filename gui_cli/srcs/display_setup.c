#include <stdio.h>
#include <string.h>
#include "display.h"

int	init_structures(t_display *d)
{
  int	i;

  d->map.width = 0;
  d->map.height = 0;
  d->nb_players = 0;
  d->nb_eggs = 0;
  d->time = 100;
  d->loop = 0;
  d->quit = 0;
  d->camera.x = 0;
  d->camera.y = 0;
  d->beholder.x = 0;
  d->beholder.y = 0;
  d->map.tiles = NULL;
  i = 0;
  while (i < 1000)
    d->players[i++].id = -1;
  i = 0;
  while (i < 1000)
    d->eggs[i++].id = -1;
  return (0);
}

SDL_Surface	*load_image(char *file_name)
{
  SDL_Surface	*s;
  SDL_Surface	*s_converted;

  s = IMG_Load(file_name);
  if (!s)
    return (NULL);
  s_converted = SDL_DisplayFormatAlpha(s);
  SDL_FreeSurface(s);
  return (s_converted);
}

/*
** This function loads every image of the game.
*/
void	load_images(t_display *d)
{
  int	i;
  char	tmp[256];

  d->ls_end = SDL_LoadBMP("./assets/screens/loading_screen_end.bmp");
  d->time_infos = load_image("./assets/UI/time_indicator.png");
  d->egg = load_image("./assets/characters/egg.png");
  d->fx_evo = load_image("./assets/FX/fx_evo.png");
  d->fx_egg = load_image("./assets/FX/egg_open.png");
  for (i = 0; i < 16; i++)
    {
      sprintf(tmp, "./assets/tiles/water%d.png", i);
      d->tiles[i] = load_image(tmp);
    }
  for (i = 0; i < 7; i++)
    {
      sprintf(tmp, "./assets/stones/caillou%d.png", i);
      d->rocks[i] = load_image(tmp);
      sprintf(tmp, "./assets/characters/pony_%d.png", i + 1);
      d->ponies[i] = load_image(tmp);
    }
  d->ponies[7] = load_image("./assets/characters/pony_8.png");
  d->black.r = 0;
  d->black.g = 0;
  d->black.b = 0;
}

/*
** This is the initializer function of the display structure.
** It puts every parameter to default value, then creates the window
** and prints the loading screen before loading the assets.
*/
int	init_display(t_display *d)
{
  if (init_structures(d) == -1)
    return (-1);
  if (SDL_Init(SDL_INIT_EVERYTHING) || TTF_Init())
    return (-1);
  SDL_WM_SetCaption("Zappy", NULL);
  d->w = SDL_SetVideoMode(1440, 900, 32, SDL_SWSURFACE);
  d->loading_screen = SDL_LoadBMP("./assets/screens/loading_screen.bmp");
  if (d->w == NULL || d->loading_screen == NULL)
    return (-1);
  display_loading_screen(d, 0);
  if (launch_music(d) == -1)
    return (-1);
  d->font = TTF_OpenFont("./assets/fonts/filxgirl.ttf", 30);
  if (!d->font)
    return (-1);
  load_images(d);
  if (strlen(SDL_GetError()) > 0)
    return (-1);
  if (display_loading_screen(d, 1) == -1)
    return (-1);
  return (0);
}
