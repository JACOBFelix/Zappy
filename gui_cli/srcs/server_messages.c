#include "commands.h"

int		game_over(t_display *d, char **tab)
{
  char		phrase[512];
  SDL_Surface	*message;
  t_coord	c;

  if (!tab[1])
    return (-1);
  phrase[0] = '\0';
  sprintf(phrase, "Game over. Team %s wins!", tab[1]);
  message = TTF_RenderText_Solid(d->font, phrase, d->black);
  c.x = 100000;
  c.y = 100000;
  if (display_image(c, message, d->w) == -1)
    return (-1);
  if (SDL_Flip(d->w) == -1)
  	return (-1);
  SDL_Delay(5000);
  return (1);
}

int		server_message(t_display *d, char **tab)
{
  char		phrase[512];
  SDL_Surface	*message;
  t_coord	c;

  if (!tab[1])
    return (-1);
  phrase[0] = '\0';
  sprintf(phrase, "Server: %s", tab[1]);
  message = TTF_RenderText_Solid(d->font, phrase, d->black);
  c.x = 100000;
  c.y = 100000;
  if (display_image(c, message, d->w) == -1)
    return (-1);
  return (0);
}
