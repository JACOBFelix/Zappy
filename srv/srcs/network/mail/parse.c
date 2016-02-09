#include <string.h>
#include "server.h"
#include "network.h"
#include "network_graphic.h"

static t_mail_parse	g_mail_parse_refs[PLAYER_ACTION_NB] =
  {
    {"avance", FORWARD, 0, PLAYER_IS_READY},
    {"droite", RIGHT, 0, PLAYER_IS_READY},
    {"gauche", LEFT, 0, PLAYER_IS_READY},
    {"voir", WATCH, 0, PLAYER_IS_READY},
    {"inventaire", INVENTARY, 0, PLAYER_IS_READY},
    {"prend", TAKE, 1, PLAYER_IS_READY},
    {"pose", DROP, 1, PLAYER_IS_READY},
    {"expulse", EJECT, 0, PLAYER_IS_READY},
    {"broadcast", BROADCAST, 1, PLAYER_IS_READY},
    {"incantation", INCANTATION, 0, PLAYER_IS_READY},
    {"fork", FORK, 0, PLAYER_IS_READY},
    {"connect_nbr", CONNECT_NBR, 0, PLAYER_IS_READY},
  };

static t_mail_parse	g_gc_parse_refs[GRAPHIC_CMD_ACTION_NB] =
  {
    {"msz", GC_MSZ, 0, GRAPHIC_IS_READY},
    {"bct", GC_BCT, 2, GRAPHIC_IS_READY},
    {"mct", GC_MCT, 0, GRAPHIC_IS_READY},
    {"tna", GC_TNA, 0, GRAPHIC_IS_READY},
    {"ppo", GC_PPO, 1, GRAPHIC_IS_READY},
    {"plv", GC_PLV, 1, GRAPHIC_IS_READY},
    {"pin", GC_PIN, 1, GRAPHIC_IS_READY},
    {"sgt", GC_SGT, 0, GRAPHIC_IS_READY},
    {"sst", GC_SST, 1, GRAPHIC_IS_READY},
    {"pnw", GC_PNW, 1, GRAPHIC_IS_READY},
  };

static int		mail_serialize_for_player(t_mail *msg,
						  t_player *from UNUSED,
						  char *content)
{
  uint32_t		i;

  for (i = 0; i < PLAYER_ACTION_NB; ++i)
    {
      if (strncmp(g_mail_parse_refs[i].str, content,
		  strlen(g_mail_parse_refs[i].str)) == 0)
	{
	  msg->action = g_mail_parse_refs[i].action;
	  return (mail_serialize_arguments(msg, content));
	}
    }
  debug_msgf("Cannot parse msg for player '%s'", content);
  return (FAILURE);
}

static int		mail_serialize_for_graphic_cmd(t_mail *msg,
						       t_player *from UNUSED,
						       char *content)
{
  uint32_t		i;

  for (i = 0; i < GRAPHIC_CMD_ACTION_NB; ++i)
    {
      if (strncmp(g_gc_parse_refs[i].str, content,
		  strlen(g_gc_parse_refs[i].str)) == 0)
	{
	  msg->action = g_gc_parse_refs[i].action;
	  return (mail_serialize_arguments(msg, content));
	}
    }
  debug_msgf("Cannot parse msg for graphic cmd '%s'", content);
  return (FAILURE);
}

/*
** note: NULL is for test.c - It will never happen in real conditions
*/
int			mail_serialize(t_mail *msg,
				       t_player *from,
				       char *content)
{
  uint32_t const	len = strlen(content);

  if (len == 0)
    return (FAILURE);
  msg->from = from;
  msg->type = (from == NULL ? PLAYER_IS_READY : from->state);
  if (msg->type == PLAYER_IS_READY)
    {
      return (mail_serialize_for_player(msg, from, content));
    }
  else if (msg->type == GRAPHIC_IS_READY)
    {
      return (mail_serialize_for_graphic_cmd(msg, from, content));
    }
  debug_msgf("Cannot parse type of the msg '%i'", msg->type);
  return (FAILURE);
}

int			mail_serialize_arguments(t_mail *msg, char *content)
{
  t_mail_parse const	action = (msg->type == PLAYER_IS_READY ?
				  g_mail_parse_refs[msg->action] :
				  g_gc_parse_refs[msg->action]);

  if (action.argument > 0)
    {
      content += strlen(action.str);
      if (content[0] != ' ' || content[1] == '\0')
	{
	  debug_msgf("No arguments '%s'", content);
	  return (FAILURE);
	}
      msg->data = strdup(content + 1);
    }
  else
    {
      if (strlen(content) != strlen(action.str))
	{
	  debug_msgf("Arguments exists '%s'", content);
	  return (FAILURE);
	}
      msg->data = NULL;
    }
  return (SUCCESS);
}
