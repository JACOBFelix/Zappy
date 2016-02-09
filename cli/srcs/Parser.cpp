#include "Parser.hpp"

Parser::Parser() {
  _types["nourriture"] = 0;
  _types["linemate"] = 1;
  _types["deraumere"] = 2;
  _types["sibur"] = 3;
  _types["mendiane"] = 4;
  _types["phiras"] = 5;
  _types["thystame"] = 6;
}

Parser::~Parser() {}

Tile Parser::oneTile(std::string const& str) {
  Tile toto;
  std::istringstream iss(str);
  std::string tmp;

  while (!iss.eof()) {
    iss >> tmp;
    if (!tmp.empty() && tmp != "joueur") {
      int i;
      try {
	i = _types.at(tmp);
      } catch(std::out_of_range) {
	throw ParserException(std::string("Item ") + tmp + " does not exist");
      }
      toto[i]++;
    }
  }
  return toto;
}

unsigned int Parser::sizeListByLevel(int const level) {
  unsigned int count = 0;

  for (register int i = 0; i <= level; ++i)
    count += i * 2 + 1;
  return count;
}

Parser *Parser::getInstance(void) {
  static Parser instance;

  return &instance;
}

std::list<Tile> *Parser::tiles(std::string const& s, int const level) {
  std::list<Tile> *retList = new std::list<Tile>();
  if (s.find('{') == std::string::npos
      || s.find('}') == std::string::npos
      || s.find('{') > s.find('}'))
    throw ParserException("`voir` command return misformated");
  std::string str = s.substr(s.find('{') + 1, s.find('}') - 1);
  std::size_t pos;

  while ((pos = str.find(',')) != std::string::npos) {
    retList->push_back(Parser::oneTile(str.substr(0, pos)));
    str = str.substr(pos + 1);
  }
  retList->push_back(Parser::oneTile(str.substr(0, pos - 1)));
  if (Parser::sizeListByLevel(level) != retList->size())
    throw ParserException("Invalid number of tiles returned");
  return retList;
}
