#include <iostream>
#include "Network.hpp"

Network::Network(Map & map, Options& options) : _options(options), _map(map), _data("") {
  int err;
  struct addrinfo hints;
  struct addrinfo *ai;

  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  if ((err = getaddrinfo(options.getHost().c_str(), options.getPort().c_str(), &hints, &ai)))
    throw NetworkException(std::string("getaddrinfo : ") + gai_strerror(err));
  if ((_socket = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol)) == -1)
    throw NetworkException(std::string("socket : ") + strerror(errno));
  if (connect(_socket, ai->ai_addr, ai->ai_addrlen) == -1) {
    close(_socket);
    throw NetworkException(std::string("connect : ") + strerror(errno));
  }
  freeaddrinfo(ai);
  _pollfds.push_back({.fd = _socket,
	.events = POLLOUT,
	.revents = 0});

  int byte_read;
  char buff_tmp[1024];

  byte_read = read(_pollfds[0].fd, buff_tmp, sizeof(buff_tmp) - 1);
  buff_tmp[byte_read] = 0;
  send(_pollfds[0].fd, (_options.getTeamName() + "\n").c_str(), (_options.getTeamName() + "\n").length(), 0);
  byte_read = read(_pollfds[0].fd, buff_tmp, sizeof(buff_tmp) - 1);
  buff_tmp[byte_read] = 0;
  byte_read = read(_pollfds[0].fd, buff_tmp, sizeof(buff_tmp) - 1);
  buff_tmp[byte_read] = 0;

  std::stringstream ss(buff_tmp);
  int size;
  ss >> size;
  _map.setWidth(size);
  ss >> size;
  _map.setHeight(size);
}

Network::~Network() {

}

Network::Network(Network const & rhs) : _options(rhs._options), _map(rhs._map), _pollfds(rhs._pollfds), _socket(rhs._socket), _data(rhs._data) {

}

Network & Network::operator=(Network const & rhs) {
  if (&rhs != this) {
    _options = rhs._options;
    _map = rhs._map;
    _socket = rhs._socket;
    _pollfds = rhs._pollfds;
    _data = rhs._data;
  }
  return *this;
}

bool		Network::socketsHandler() {
  int status;
  int byte_read;
  char buff_tmp[1024];

  if ((status = poll(_pollfds.data(), _pollfds.size(), -1)) == -1)
    throw NetworkException(std::string("poll : ") + strerror(errno));
  else if (status == 0)
    std::cout << "Nothing to read" << std::endl;
  else {
    if (_pollfds[0].revents & POLLIN) {
      byte_read = recv(_pollfds[0].fd, buff_tmp, sizeof(buff_tmp) - 1, 0);
      buff_tmp[byte_read] = 0;
      _data = buff_tmp;
      return true;
    }
  }
  return false;
}

std::string const &		Network::getData(void) const {
  return _data;
}

void		Network::sendData(std::string const &data) {
  if (_pollfds[0].revents & POLLOUT) {
    send(_pollfds[0].fd, std::string(data + "\n").data(), data.size() + 1, 0);
    _pollfds[0].events = POLLIN;
  }
}

void		Network::setOutput() {
  _pollfds[0].events = POLLIN | POLLOUT;
}
