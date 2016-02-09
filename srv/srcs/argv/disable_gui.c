#include "server.h"

int32_t	disable_gui(t_server *t, UNUSED uint32_t i, UNUSED uint32_t ac,
		    UNUSED char **tab)
{
  t->gui_down = 0;
  return (i + 1);
}
