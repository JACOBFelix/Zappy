#include "Player.hpp"

Player::Player(int const w, int const h, std::string const& teamName) :
  _width(w),
  _height(h),
  _level(1),
  _dir(NORTH),
  _pos(std::pair<int,int>(0, 0)),
  _inv({10, 0, 0, 0, 0, 0, 0}),
  _requirement({false, true, false, false, false, false, false}),
  _incant({
      {0, 0, 0, 0, 0, 0, 0},
	{1, 1, 0, 0, 0, 0, 0},
	  {2, 1, 1, 1, 0, 0, 0},
	    {2, 2, 0, 1, 0, 2, 0},
	      {4, 1, 1, 2, 0, 1, 0},
		{4, 1, 2, 1, 3, 0, 0},
		  {6, 1, 2, 3, 0, 1, 0},
		    {6, 2, 2, 2, 2, 2, 1}
    }),
  _moveTab({
      std::pair<int, int>(0, 1),
	std::pair<int, int>(1, 0),
	std::pair<int, int>(0, -1),
	std::pair<int, int>(-1, 0),
	}),
  _teamName(teamName) {}

Player::~Player() {}

Player::Player(Player const &) {}

Player & Player::operator=(Player const & rhs) {
  if (&rhs != this) {
  }
  return *this;
}

bool				Player::canEvolve(){
  std::vector<int>::iterator invIt = _inv.begin() + 1;
  std::vector<int>::iterator incantIt = _incant[_level].begin() + 1;

  for (; invIt != _inv.end(); ++invIt, ++incantIt) {
    if (*invIt != *incantIt)
      return false;
  }
  return true;
}

bool				Player::hasEnoughFood(int v) {
  if (_inv[0] > v)
    return true;
  return false;
}

int				Player::getLevel() const {
  return _level;
}

void Player::setLevel(int const level) {
  if (_level < LEVEL_MAX)
    _level = level;
}

std::vector<int> const& Player::getInv(void) const {
  return _inv;
}

void				Player::moveForward(void) {
  _pos.first = (_pos.first + _moveTab[_dir].first + _width) % _width;
  _pos.second = (_pos.second + _moveTab[_dir].second + _height) % _height;
}

std::pair<int,int> const &	Player::getPos() const {
  return _pos;
}

void				Player::turnLeft() {
  _dir = (Player::direction)(((int)_dir - 1 + 4) % 4);
}

void				Player::turnRight() {
  _dir = (Player::direction)(((int)_dir + 1 + 4) % 4);
}

Player::direction const &	Player::getDir(void) const {
  return _dir;
}

std::vector<int> const &	Player::getIncant(void) const {
  return _incant[_level];
}

std::vector<bool> const &	Player::getRequirement(void) const {
  return _requirement;
}

void				Player::setRequirement(int item, bool status) {
  _requirement[item] = status;
}

void				Player::deleteItem(int item) {
  --_inv[item];
}

void				Player::addItem(int item) {
  --_inv[item];
}

int& Player::getWidth(void) {
  return _width;
}

void Player::setWidth(int const w) {
  _width = w;
}

int& Player::getHeight(void) {
  return _height;
}

void Player::setHeight(int const h) {
  _height = h;
}

std::string const& Player::getTeamName(void) const {
  return _teamName;
}
