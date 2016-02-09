#pragma once

#include <vector>
#include <string>
#include <cstring>
#include <netdb.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <unistd.h>
#include "Exceptions.hpp"
#include "Map.hpp"
#include "Options.hpp"

class Network {
private:
  Options& _options;
  Map& _map;
  std::vector<struct pollfd> _pollfds;
  int _socket;
  std::string _data;

public:
  Network(Map& map, Options& _options);
  ~Network();
  Network(Network const &);
  Network& operator=(Network const &);

  bool		socketsHandler(void);
  std::string const &		getData(void) const;
  void		sendData(std::string const &);
  void		setOutput(void);
};
