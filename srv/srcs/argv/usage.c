#include "server.h"

uint8_t		usage(char *prog)
{
  printf("usage: %s [ -p PORT ] [ -x WIDTH ] [ -y HEIGHT ] [ -c\
  NB_CLIENTS_BY_TEAM ] [ -t DELAY ] [ -g ] -n TEAM1_NAME [\
  TEAM2_NAME .. ]\n", prog);
  return (-1);
}
