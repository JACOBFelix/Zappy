#if defined TEST_MODE && defined TEST_MAIL

# include <assert.h>
# include <stdio.h>
# include <string.h>
# include "network.h"
# include "server.h"

int	main()
{
  printf("\n===== MAIL PARSING TESTS =====\n");
  test_mail_parsing_simple_failure1();
  test_mail_parsing_simple_success1();
  test_mail_parsing_simple_success2();
  printf("\n===== MAIL ACTIONS TESTS =====\n");
  test_mail_action_broadcast();
  return (0);
}

#endif
