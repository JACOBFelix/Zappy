#pragma once

#include <string>
#include <map>
#include <list>
#include <vector>
#include "Tile.hpp"
#include "Parser.hpp"
#include "Player.hpp"

class Map {
private:
  Player& _player;
  int& _width;
  int& _height;
  std::map<std::pair<int, int>, Tile> _tiles;

public:
  Map(int& w, int& h, Player& player);
  ~Map();
  Map(Map const &);
  Map& operator=(Map const &);

  void update(std::string const &, std::pair<int, int>, Player::direction, int);

  int getWidth(void) const;
  int getHeight(void) const;
  std::map<std::pair<int, int>, Tile>& getTiles(void);

  void setWidth(int const w);
  void setHeight(int const h);

  std::pair<int, int> gemNearPlayer(int const n, std::vector<bool> const wanted);
};
