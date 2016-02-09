#include "PathFinding.hpp"

PathFinding::PathFinding(Map & map) :
  _map(map) {

}

PathFinding::~PathFinding() {

}

PathFinding::PathFinding(PathFinding const & rhs) : _map(rhs._map){

}

PathFinding & PathFinding::operator=(PathFinding const & rhs) {
  if (&rhs != this) {

  }
  return *this;
}

void		PathFinding::popLastPos(void) {
  _moveInstruction.pop_front();
}

bool PathFinding::isEmpty(void) const {
  return _moveInstruction.empty();
}

PathFinding::MoveInstruction PathFinding::getNextInstruction() const {
  return _moveInstruction.front();
}

int		PathFinding::sizePath(int const & a, int const & b) {
  int size;

  if (ABS(a - b) > _map.getWidth() / 2)
    size = (_map.getWidth() - b) + (_map.getWidth() + a);
  else
    size = ABS(a - b);
  return size;
}

#define MIN(a, b)	(a < b ? a : b)
#define MAX(a, b)	(a < b ? b : a)
void		PathFinding::pushDataToStack(int x1, int x2) {
  int i = MIN(x1, x2);

  for (; i < MAX(x1, x2); ++i) {
    _moveInstruction.push_back(FORWARD);
  }
}

# define DIRHORI(a, b) (a < b ? Player::EAST : Player::WEST)
# define DIRVERT(a, b) (a < b ? Player::NORTH : Player::SOUTH)

void		PathFinding::clearList() {
  while (!_moveInstruction.empty()) {
    _moveInstruction.pop_back();
  }
}

void		PathFinding::computeNextPos(Player const & player, std::pair<int, int> & pos) {
  clearList();
  int tmpDir = player.getDir();

  if (player.getPos().first != pos.first) {
    while (tmpDir != DIRHORI(player.getPos().first, pos.first)) {
      _moveInstruction.push_back(RIGHT);
      tmpDir = (tmpDir + 1) % 4;
    }
    pushDataToStack(player.getPos().first, pos.first);
  }
  if (player.getPos().second != pos.second) {
    while (tmpDir != DIRVERT(player.getPos().second, pos.second)) {
      _moveInstruction.push_back(RIGHT);
      tmpDir = (tmpDir + 1) % 4;
    }
    pushDataToStack(player.getPos().second, pos.second);
  }
}
