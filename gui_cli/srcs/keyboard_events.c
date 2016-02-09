#include <unistd.h>
#include "display.h"

/*
** The camera is updated with the keyboard inputs.
** It is reinitialized if it goes farther than one map width or height,
** to prevent problems with number precision.
*/
void	update_camera(t_display *d, Uint32 time_elapsed)
{
  d->camera.x += d->beholder.x * (time_elapsed * 3.0f);
  d->camera.y += d->beholder.y * (time_elapsed * 3.0f);
  if (d->camera.x > d->map.width * 1000)
    d->camera.x = d->camera.x % d->map.width;
  else if (d->camera.x < -(d->map.width * 1000))
    d->camera.x += d->map.width * 1000;
  if (d->camera.y > d->map.height * 1000)
    d->camera.y = d->camera.y % d->map.height;
  else if (d->camera.y < -(d->map.height * 1000))
    d->camera.y += d->map.height * 1000;
}

void	update_game_time(t_display *d, int increment, int fd_server)
{
  int	new_time;
  char	tmp[256];

  if (increment)
    new_time = d->time * 2;
  else
    new_time = d->time / 2;
  if (new_time <= 0)
    return ;
  sprintf(tmp, "sst %d\n", new_time);
  write(fd_server, tmp, sizeof(tmp) - 1);
}

void	update_music(t_display *d)
{
  if (d->music_on)
    {
      SDL_PauseAudio(1);
      d->music_on = 0;
    }
  else
    {
      SDL_PauseAudio(0);
      d->music_on = 1;
    }
}

void	mouse_events(t_display *d, int fd_server)
{
  if (d->e.button.x >= 1333 && d->e.button.x <= 1350
      && d->e.button.y >= 13 && d->e.button.y <= 30)
    update_game_time(d, 1, fd_server);
  else if (d->e.button.x >= 1373 && d->e.button.x <= 1391
	   && d->e.button.y >= 13 && d->e.button.y <= 30)
    update_game_time(d, 0, fd_server);
}

void	keyboard_events(t_display *d, Uint32 time_elapsed, int fd_server)
{
  while (SDL_PollEvent(&d->e))
    {
      if (d->e.key.keysym.sym == SDLK_ESCAPE)
	d->quit = 1;
      if (d->e.key.keysym.sym == SDLK_z)
  d->beholder.y = (d->e.type == SDL_KEYDOWN) ? (-1) : (0);
      else if (d->e.key.keysym.sym == SDLK_s)
  d->beholder.y = (d->e.type == SDL_KEYDOWN) ? (1) : (0);
      else if (d->e.key.keysym.sym == SDLK_q)
  d->beholder.x = (d->e.type == SDL_KEYDOWN) ? (-1) : (0);
      else if (d->e.key.keysym.sym == SDLK_d)
  d->beholder.x = (d->e.type == SDL_KEYDOWN) ? (1) : (0);
      if (d->e.key.keysym.sym == SDLK_m && d->e.type == SDL_KEYDOWN)
	update_music(d);
      if (d->e.type == SDL_MOUSEBUTTONDOWN)
	mouse_events(d, fd_server);
    }
  update_camera(d, time_elapsed);
}
