#include <stdio.h>
#include <string.h>
#include "display.h"

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

void	load_images(t_display *d)
{
  int	i;
  char	tmp[256];

  d->ls_end = SDL_LoadBMP("./assets/screens/loading_screen_end.bmp");
  d->inventory = IMG_Load("./assets/UI/inventaire.png");
  d->playerinfo = IMG_Load("./assets/UI/player_info.png");
  d->tile = IMG_Load("./assets/tiles/tile.png");
  d->egg = IMG_Load("./assets/characters/egg.png");
  d->fx_evo = IMG_Load("./assets/FX/fx_evo.png");
  d->fx_egg = IMG_Load("./assets/FX/egg_open.png");
  i = 0;
  while (i < 7)
    {
      tmp[0] = '\0';
      sprintf(tmp, "./assets/stones/caillou%d.png", i);
      d->rocks[i] = IMG_Load(tmp);
      tmp[0] = '\0';
      sprintf(tmp, "./assets/characters/pony_%d.png", i + 1);
      d->ponies[i] = IMG_Load(tmp);
      i++;
    }
  d->ponies[7] = IMG_Load("./assets/characters/pony_8.png");
  d->black.r = 0;
  d->black.g = 0;
  d->black.b = 0;
}

int	init_display(t_display *d)
{
  d->quit = 0;
  d->loop = 0;
  d->camera_x = 0;
  d->camera_y = 0;
  d->beholder.x = 0;
  d->beholder.y = 0;
  if (SDL_Init(SDL_INIT_EVERYTHING) || TTF_Init())
      return (-1);
  SDL_WM_SetCaption("Zappy", NULL);
  d->w = SDL_SetVideoMode(1440, 900, 32, SDL_SWSURFACE);
  d->loading_screen = SDL_LoadBMP("./assets/screens/loading_screen.bmp");
  if (d->w == NULL || d->loading_screen == NULL)
      return (-1);
  display_loading_screen(d, 0);
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

int	manage_display(t_display *d, t_server *s)
{
  if (d->quit || s->gui_down == 1)
    return (0);
  keyboard_events(d, s);
  if (d->quit)
    return (0);
  SDL_FillRect(d->w, NULL, 0x00);
  if (display_map(d, s) == -1)
    {
      close_display(d, 1);
      return (-1);
    }
  if (SDL_Flip(d->w) == -1)
    {
      close_display(d, 1);
      return (-1);
    }
  d->loop++;
  return (0);
}

void	close_display(t_display *d, int abort)
{
  int	i;

  if (abort == 1)
  {
    printf("Something went wrong: %s\nAborting display\n", SDL_GetError());
    SDL_Quit();
    d->quit = 1;
  }
  if (d->quit)
    return ;
  i = 0;
  while (i < 8)
    SDL_FreeSurface(d->ponies[i++]);
  i = 0;
  while (i < 7)
    SDL_FreeSurface(d->rocks[i++]);
  SDL_FreeSurface(d->loading_screen);
  SDL_FreeSurface(d->ls_end);
  SDL_FreeSurface(d->inventory);
  SDL_FreeSurface(d->playerinfo);
  SDL_FreeSurface(d->tile);
  SDL_FreeSurface(d->egg);
  SDL_FreeSurface(d->fx_evo);
  SDL_FreeSurface(d->fx_egg);
  SDL_Quit();
}
