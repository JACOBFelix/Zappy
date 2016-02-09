#pragma once

#include <utility>
#include <list>
#include "Map.hpp"
#include "Player.hpp"

#define ABS(x) (x > 0 ? x : -(x))

class PathFinding {
public:
  enum MoveInstruction {FORWARD, RIGHT, LEFT};

private:
  Map & _map;
  std::list<MoveInstruction> _moveInstruction;

public:
  PathFinding(Map &);
  ~PathFinding();
  PathFinding(PathFinding const &);
  PathFinding & operator=(PathFinding const &);

  bool isEmpty(void) const;
  void popLastPos(void);
  MoveInstruction getNextInstruction() const;

  int	sizePath(int const &, int const &);
  void	pushDataToStack(int, int);
  void	clearList(void);
  void	computeNextPos(Player const & , std::pair<int, int> & );
};
