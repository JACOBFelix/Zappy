#include "commands.h"

int	egg_new(t_display *d, char **tab)
{
  if (!tab[1] || !tab[2] || !tab[3] || !tab[4])
    return (-1);
  d->eggs[d->nb_eggs].id = atoi(tab[1]);
  d->eggs[d->nb_eggs].pos.x = atoi(tab[3]);
  d->eggs[d->nb_eggs].pos.y = atoi(tab[4]);
  d->eggs[d->nb_eggs].status = IDLE;
  d->nb_eggs++;
  return (0);
}

int	egg_hatching(t_display *d, char **tab)
{
  int	i;

  if (!tab[1])
    return (-1);
  i = get_egg(d, atoi(tab[1]));
  if (i < 0)
    return (-1);
  d->eggs[i].status = HATCHING;
  return (0);
}

int	egg_connecting(t_display *d, char **tab)
{
  int	i;

  if (!tab[1])
    return (-1);
  i = get_egg(d, atoi(tab[1]));
  if (i < 0)
    return (-1);
  d->eggs[i].status = IDLE;
  return (0);
}

int	egg_dying(t_display *d, char **tab)
{
  int	i;

  if (!tab[1])
    return (-1);
  i = get_egg(d, atoi(tab[1]));
  if (i < 0)
    return (-1);
  d->eggs[i].status = DEAD;
  return (0);
}
