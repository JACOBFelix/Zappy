#include "display.h"

void	update_camera(t_display *d, t_server *s)
{
  d->camera_x += d->beholder.x * 100;
  d->camera_y += d->beholder.y * 100;
  if (d->camera_x > (int)s->world_width * 1000)
    d->camera_x = d->camera_x % s->world_width;
  else if (d->camera_x < -((int)s->world_width * 1000))
    d->camera_x += s->world_width * 1000;
  if (d->camera_y > (int)s->world_height * 1000)
    d->camera_y = d->camera_y % s->world_height;
  else if (d->camera_y < -((int)s->world_height * 1000))
    d->camera_y += s->world_height * 1000;
}

void	keyboard_events(t_display *d, t_server *s)
{
  while (SDL_PollEvent(&d->e))
    {
      if (d->e.key.keysym.sym == SDLK_ESCAPE)
	{
	  close_display(d, 0);
	  d->quit = 1;
	}
      if (d->e.key.keysym.sym == SDLK_z)
	d->beholder.y = (d->e.type == SDL_KEYDOWN) ? (-1) : (0);
      else if (d->e.key.keysym.sym == SDLK_s)
	d->beholder.y = (d->e.type == SDL_KEYDOWN) ? (1) : (0);
      else if (d->e.key.keysym.sym == SDLK_q)
	d->beholder.x = (d->e.type == SDL_KEYDOWN) ? (-1) : (0);
      else if (d->e.key.keysym.sym == SDLK_d)
	d->beholder.x = (d->e.type == SDL_KEYDOWN) ? (1) : (0);
    }
  update_camera(d, s);
}
