#include "display.h"

int		display_ui(t_display *d)
{
  t_coord	c;
  char		phrase[256];
  SDL_Surface	*descr;

  c.x = 940000;
  c.y = 0;
  if (display_image(c, d->time_infos, d->w) == -1)
    return (-1);
  sprintf(phrase, "Current game frequency : %dHz", d->time);
  descr = TTF_RenderText_Solid(d->font, phrase, d->black);
  if (!descr)
    return (-1);
  c.y = 5000;
  c.x = 1000000;
  return (display_image(c, descr, d->w));
}
