CC	= gcc

RM	= rm -f

GUIDIR	= gui_cli
GUINAME	= zappy_gui

SRVDIR	= srv
SRVNAME	= zappy_server

AIDIR	= cli
AINAME	= zappy_ai

all:	$(GUINAME) $(SRVNAME) $(AINAME)

$(GUINAME):
	make -C$(GUIDIR)
	cp $(GUIDIR)/$(GUINAME) $(GUINAME)

$(SRVNAME):
	make -C$(SRVDIR)
	cp $(SRVDIR)/$(SRVNAME) $(SRVNAME)

$(AINAME):
	make -C$(AIDIR)
	cp $(AIDIR)/$(AINAME) $(AINAME)


clean:
	make clean -C$(GUIDIR)
	make clean -C$(SRVDIR)
	make clean -C$(AIDIR)

fclean:
	make fclean -C$(GUIDIR)
	make fclean -C$(SRVDIR)
	make fclean -C$(AIDIR)
	$(RM) $(SRVNAME) $(GUINAME) $(AINAME)

re:	fclean all

.PHONY:	all clean fclean re $(GUINAME) $(SERVNAME) $(AINAME)
