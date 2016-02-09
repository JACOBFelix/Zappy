#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "network.h"

int		test_mail_action_broadcast()
{
  test_mail_action_broadcast_distance();
  test_mail_action_broadcast_index_max_float();
  test_mail_action_broadcast_find_angle();
  return (0);
}

int		test_mail_action_broadcast_distance()
{
  float const	d00 = distance(0, 0, 0, 0);
  float const	d01 = distance(0, 0, 0, 1);
  float const	d10 = distance(0, 0, 1, 0);
  float const	d11 = distance(0, 0, 1, 1);
  float const	d22 = distance(0, 0, 2, 2);
  float const	d_3_3 = distance(0, 0, -3, -3);
  float const	d33 = distance(0, 0, 3, 3);

  printf("=== Test Broadcast#distance running ===\n");
  assert(d00 == 0);
  assert((d10 == d01) == 1.0);
  assert(d11 > d01);
  assert(d22 > d11);
  assert(d_3_3 == d33);
  printf("ok\n");
  return (0);
}

int	test_mail_action_broadcast_index_max_float()
{
  float	tab1[5] = {1, 2, 3, 4, 5};
  float	tab2[5] = {5, 4, 3, 2, 1};
  float	tab3[5] = {1, 2, 3, 4, 1};
  float	tab4[5] = {1, 2, 6, 4, 1};

  printf("=== Test Broadcast#index_max_float running ===\n");
  assert(index_max_float(tab1, 5) == 5);
  assert(index_max_float(tab2, 5) == 0);
  assert(index_max_float(tab3, 5) == 4);
  assert(index_max_float(tab4, 5) == 3);
  printf("ok\n");
  return (0);
}

int		test_mail_action_broadcast_find_angle()
{
  t_pos const	o = {0, 0};
  t_pos const	a = {0, -1};
  t_pos const	b = {0, 1};
  t_pos const	c = {1, -1};
  t_pos const	d = {1, 0};
  t_pos const	e = {1, 1};
  t_pos const	f = {1, -1};
  t_pos const	g = {1, 0};
  t_pos const	h = {1, 1};

  assert(action_broadcast_find_angle(&o, &o) == 0);
  assert(action_broadcast_find_angle(&o, &a) == 5);
  assert(action_broadcast_find_angle(&o, &b) == 1);
  assert(action_broadcast_find_angle(&o, &c) == 4);
  assert(action_broadcast_find_angle(&o, &d) == 3);
  assert(action_broadcast_find_angle(&o, &e) == 2);
  assert(action_broadcast_find_angle(&o, &f) == 6);
  assert(action_broadcast_find_angle(&o, &g) == 7);
  assert(action_broadcast_find_angle(&o, &h) == 8);
  return (0);
}
