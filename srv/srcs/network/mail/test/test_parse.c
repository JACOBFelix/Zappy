#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "network.h"
#include "server.h"

int		test_mail_parsing_simple_success1()
{
  t_mail	msg;

  printf("=== Successful tests 1 running ===\n");
  assert(mail_serialize(&msg, NULL, "avance") == SUCCESS);
  assert(msg.action == FORWARD);
  assert(msg.from == NULL);
  assert(msg.data == NULL);
  assert(mail_serialize(&msg, NULL, "droite") == SUCCESS);
  assert(msg.action == RIGHT);
  assert(msg.from == NULL);
  assert(msg.data == NULL);
  assert(mail_serialize(&msg, NULL, "prend objet") == SUCCESS);
  assert(msg.action == TAKE);
  assert(msg.from == NULL);
  assert(msg.data != NULL);
  assert(strcmp(msg.data, "objet") == 0);
  printf("ok\n");
  return (0);
}

int		test_mail_parsing_simple_success2()
{
  printf("=== Successful tests 2 running ===\n");
  test_mail_parsing_simple_success2_1();
  test_mail_parsing_simple_success2_2();
  test_mail_parsing_simple_success2_3();
  printf("ok\n");
  return (0);
}

int		test_mail_parsing_simple_success2_1()
{
  t_mail	msg;

  assert(mail_serialize(&msg, NULL, "avance") == SUCCESS);
  assert(msg.action == FORWARD);
  assert(mail_serialize(&msg, NULL, "droite") == SUCCESS);
  assert(msg.action == RIGHT);
  assert(mail_serialize(&msg, NULL, "gauche") == SUCCESS);
  assert(msg.action == LEFT);
  assert(mail_serialize(&msg, NULL, "voir") == SUCCESS);
  assert(msg.action == WATCH);
  assert(mail_serialize(&msg, NULL, "inventaire") == SUCCESS);
  assert(msg.action == INVENTARY);
  return (0);
}

int		test_mail_parsing_simple_success2_2()
{
  t_mail	msg;

  assert(mail_serialize(&msg, NULL, "prend o") == SUCCESS);
  assert(msg.action == TAKE);
  assert(mail_serialize(&msg, NULL, "pose o") == SUCCESS);
  assert(msg.action == DROP);
  assert(mail_serialize(&msg, NULL, "expulse") == SUCCESS);
  assert(msg.action == EJECT);
  assert(mail_serialize(&msg, NULL, "broadcast t") == SUCCESS);
  assert(msg.action == BROADCAST);
  return (0);
}

int		test_mail_parsing_simple_success2_3()
{
  t_mail	msg;

  assert(mail_serialize(&msg, NULL, "incantation") == SUCCESS);
  assert(msg.action == INCANTATION);
  assert(mail_serialize(&msg, NULL, "fork") == SUCCESS);
  assert(msg.action == FORK);
  assert(mail_serialize(&msg, NULL, "connect_nbr") == SUCCESS);
  assert(msg.action == CONNECT_NBR);
  return (0);
}
