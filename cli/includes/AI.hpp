#include <list>
#include <vector>
#include "Map.hpp"
#include "Player.hpp"
#include "PathFinding.hpp"

#define UNUSED __attribute__((unused))

class AI {
public:
  enum actionType {FORWARD, RIGHT, LEFT, LOOK, INV, PICK, DROP, EXPULSE, BROADCAST, INCANT, FORK, SLOT };
  enum objects {FOOD, LINEMATE, DERAUMERE, SIBUR, MENDIANE, PHIRAS, THYSTAME};

private:
  Player& _player;
  Map& _map;
  std::vector<std::string> const _typeText;
  std::vector<std::string> const _typeObjects;

  std::vector<std::pair<std::string, bool (AI::*)(std::string const&)> > _ptrNextAction;
  std::vector<bool (AI::*)(void)> _actionPtr;

  actionType _actionType;
  std::list<std::string> _actions;
  std::list<AI::actionType> _types;
  int _object;

  PathFinding	_pf;

  void			moveToPos(std::pair<int, int> const &);
  void			addAction(actionType);
  void			addAction(actionType, std::string const);
  void			addAction(PathFinding::MoveInstruction);

  void			explore(void);

  void			pickAll(void);
  void			pickObject(int);
  void			dropObject(int);
  void			checkForGems(void);

  void			evolve(void);
  void			tryToEvolve(void);
  void			checkPlayerFood(void);

  bool			forward(void);
  bool			right(void);
  bool			left(void);
  bool			look(void);
  bool			inventory(void);
  bool			take(void);
  bool			drop(void);
  bool			expulse(void);
  bool			broadcast(void);
  bool			incantation(void);
  bool			fork(void);
  bool			slot(void);

  bool			updateData(std::string const &);

  bool			computeNextAction(std::string const& data);
  bool			actionError(std::string const& data);
  bool			dead(std::string const& data);
  bool			evolving(std::string const& data);
  bool			incantation2(std::string const& data);

public:
  AI(Player&, Map &);
  ~AI();
  AI(AI const &);
  AI& operator=(AI const &);

  bool		        computeAction(std::string const &);
  std::string const &	getAction(void) const;
};
