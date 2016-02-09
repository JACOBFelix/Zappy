#pragma once

#include <thread>
#include "Network.hpp"
#include "Map.hpp"
#include "AI.hpp"
#include "Gui.hpp"
#include "Options.hpp"
#include "Player.hpp"

class Client {
private:
  Options _options;
  Player _player;
  Map _map;
  AI _ai;
  Network _network;
  Gui _gui;
  std::thread _guiThread;

public:
  Client(Options& options);
  ~Client();
  Client(Client const&);
  Client& operator=(Client const&);

  void		run(void);
  static void guiThread(Gui *gui);
};
