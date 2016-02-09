#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "server.h"

void		debug_msg(char *s)
{
#ifdef DEBUG
  printf("[DEBUG] %s\n", s);
#else
  (void)s;
#endif
}

void		debug_msgf(char *fmt, ...)
{
#ifdef DEBUG
  char		buffer[512];
  va_list	ap;

  memset(buffer, 0, sizeof(buffer));
  va_start(ap, fmt);
  vsnprintf(buffer, sizeof(buffer) - 1, fmt, ap);
  printf("[DEBUG] %s\n", buffer);
  va_end(ap);
#else
  (void)fmt;
#endif
}
