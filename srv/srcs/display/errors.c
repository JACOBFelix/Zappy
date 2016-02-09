#include <errno.h>
#include <string.h>
#include <stdarg.h>
#include "server.h"

int32_t		print_error(char *msg)
{
  printf("error: %s\n", msg);
  return (FAILURE);
}

int32_t		print_errorf(char *fmt, ...)
{
#ifdef DEBUG
  char		buffer[512];
  va_list	ap;

  memset(buffer, 0, sizeof(buffer));
  va_start(ap, fmt);
  vsnprintf(buffer, sizeof(buffer) - 1, fmt, ap);
  printf("error: %s\n", buffer);
  va_end(ap);
#else
  (void)fmt;
#endif
  return (FAILURE);
}

int32_t		derror(char *msg)
{
  if (errno != EINTR)
  {
    perror(msg);
  }
  return ((errno != EINTR) ? (FAILURE) : (SUCCESS));

}
