#include "commands.h"

int	server_unknown_command(__attribute__((unused)) t_display *d,
				 __attribute__((unused)) char **tab)
{
  return (0);
}

int	server_bad_parameter(__attribute__((unused)) t_display *d,
			     __attribute__((unused)) char **tab)
{
  return (0);
}
