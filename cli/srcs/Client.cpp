#include "Client.hpp"

Client::Client(Options& options) : _options(options), _player(0, 0, _options.getTeamName()), _map(_player.getWidth(), _player.getHeight(), _player), _ai(_player, _map), _network(_map, _options), _gui(_player, _map, _options.getGui()), _guiThread(Client::guiThread, &_gui) {}

Client::~Client() {}

Client::Client(Client const& rhs) : _options(rhs._options), _player(rhs._player), _map(rhs._map), _ai(rhs._ai), _network(rhs._network), _gui(rhs._gui) {}

Client & Client::operator=(Client const& rhs) {
  if (&rhs != this) {
    _player = rhs._player;
    _options = rhs._options;
    _ai = rhs._ai;
    _network = rhs._network;
    _map = rhs._map;
    _gui = rhs._gui;
  }
  return *this;
}

void		Client::run() {
  _guiThread.detach();
  while (true) {
    _network.socketsHandler();
    if (_ai.computeAction(_network.getData()))
      _network.setOutput();
    _network.sendData(_ai.getAction());
  }
}

void		Client::guiThread(Gui *gui) {
  gui->update();
}
