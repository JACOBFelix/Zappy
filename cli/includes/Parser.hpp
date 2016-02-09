#pragma once

#include <string>
#include <sstream>
#include <list>
#include <map>
#include <exception>
#include "Exceptions.hpp"
#include "Tile.hpp"

class Parser {
private:
  std::map<std::string const, int> _types;
  Tile oneTile(std::string const& str);
  unsigned int sizeListByLevel(int const level);

  Parser();
  ~Parser();

public:
  static Parser *getInstance(void);
  std::list<Tile> *tiles(std::string const& str, int const level);
};
