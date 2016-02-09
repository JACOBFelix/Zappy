#include "Map.hpp"

Map::Map(int& w, int& h, Player& player) : _player(player), _width(w), _height(h) {}

Map::~Map() {}

Map::Map(Map const & rhs) : _player(rhs._player), _width(rhs._width), _height(rhs._height) {}

Map & Map::operator=(Map const & rhs) {
  if (&rhs != this) {
    _player = rhs._player;
    _width = rhs._width;
    _height = rhs._height;
  }
  return *this;
}

void		Map::update(std::string const& str, std::pair<int, int> pos, Player::direction const dir, int const level) {
  std::list<Tile> *tiles = Parser::getInstance()->tiles(str, level);
  std::list<Tile>::iterator it = tiles->begin();
  int x = dir == Player::WEST || dir == Player::NORTH ? -1 : 1;

  for (int i = 0; i <= level; ++i) {
    for (int j = -i; j <= i && it != tiles->end(); ++j, ++it) {
      if (dir == Player::NORTH || dir == Player::SOUTH)
	_tiles[std::pair<int, int>((pos.first + j + _width) % _width, (pos.second + i * x + _height) % _height)] = *it;
      else
	_tiles[std::pair<int, int>((pos.first + i * x + _width) % _width, (pos.second + j + _height) % _height)] = *it;
    }
  }
  delete tiles;
}

int		Map::getWidth(void) const {
  return _width;
}

int		Map::getHeight(void) const {
  return _height;
}

std::map<std::pair<int, int>, Tile>& Map::getTiles(void) {
  return _tiles;
}

void		Map::setWidth(int const w) {
  _width = w;
}

void		Map::setHeight(int const h) {
  _height = h;
}

std::pair<int, int>		Map::gemNearPlayer(int const n, std::vector<bool> const wanted) {
  std::pair<int, int> pos;

  for (int i = 0; i < n; ++i) {
    for (pos.first = _player.getPos().first - i; pos.first <= _player.getPos().second + i; ++pos.first) {
      for (pos.second = _player.getPos().second - i; pos.second <= _player.getPos().second + i; ++pos.second) {
	int j = 0;
	for (std::vector<bool>::const_iterator it = wanted.begin(); it != wanted.end(); ++it, ++j) {
	  if ((*it) && _tiles[std::pair<int, int>((pos.first + _width) % _width,
						  (pos.second + _height) % _height)][j] > 0)
	    return pos;
	}
      }
    }
  }
  return std::pair<int, int>(n + 1, n + 1);
}
