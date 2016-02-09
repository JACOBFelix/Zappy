#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "network.h"
#include "server.h"

int		test_mail_parsing_simple_failure1()
{
  t_mail	msg;

  printf("=== Failure tests 1 running ===\n");
  assert(mail_serialize(&msg, NULL, "avanceRRRR") == FAILURE);
  assert(mail_serialize(&msg, NULL, "avance de 2 cases") == FAILURE);
  assert(mail_serialize(&msg, NULL, "prend") == FAILURE);
  printf("ok\n");
  return (0);
}
