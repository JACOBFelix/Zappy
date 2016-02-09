#include <iostream>
#include "Options.hpp"
#include "Exceptions.hpp"

Options::Options() {
  _port = "4242";
  _host = "127.0.0.1";
  _gui = false;
  _teamName = "poney";
}

Options::~Options() {}

Options::Options(Options const& rhs) : _port(rhs._port), _host(rhs._host), _gui(rhs._gui), _teamName(rhs._teamName) {}

Options& Options::operator=(Options const& rhs) {
  if (&rhs != this) {
    _port = rhs._port;
    _host = rhs._host;
    _gui = rhs._gui;
    _teamName = rhs._teamName;
  }
  return *this;
}

bool Options::parse(int const ac, char const *const *const args) {
  for (int i = 1; i < ac; ++i) {
    if (std::string(args[i]) == "-g" || std::string(args[i]) == "--gui")
      _gui = true;
    else if (std::string(args[i]) == "--no-gui")
      _gui = false;
    else if (std::string(args[i]) == "-p" || std::string(args[i]) == "--port") {
      if (i + 1 == ac)
	throw ArgumentException("Invalid port argument");
      _port = args[++i];
    }
    else if (std::string(args[i]) == "-h" || std::string(args[i]) == "--host") {
      if (i + 1 == ac)
	throw ArgumentException("Invalid host argument");
      _host = args[++i];
    }
    else if (std::string(args[i]) == "-n" || std::string(args[i]) == "--team-name") {
      if (i + 1 == ac)
	throw ArgumentException("Invalid team name argument");
      _teamName = args[++i];
    }
    else if (std::string(args[i]) == "--help") {
      std::cout << "Usage:" << args[0] << ": [-p|--port port] [-h|--host host] [-n|--team-name name] [--help] [-g|--gui] [--no-gui]" << std::endl;
      return false;
    }
  }
  return true;
}

std::string const& Options::getPort(void) const {
  return _port;
}

void Options::setPort(std::string const& port) {
  _port = port;
}

std::string const& Options::getHost(void) const {
  return _host;
}

void Options::setHost(std::string const& host) {
  _host = host;
}

bool Options::getGui(void) const {
  return _gui;
}

void Options::setGui(bool const gui) {
  _gui = gui;
}

std::string const& Options::getTeamName(void) const {
  return _teamName;
}

void Options::setTeamName(std::string const& teamName) {
  _teamName = teamName;
}
