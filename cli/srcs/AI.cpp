#include <iostream>
#include "AI.hpp"

AI::AI(Player& player, Map& map) :
  _player(player),
  _map(map),
  _typeText({"avance", "droite", "gauche", "voir",
	"inventaire", "prend ", "pose ", "expulse",
	"broadcast ","incantation", "fork", "connect_nbr"}),
  _typeObjects({"nourriture", "linemate", "deraumere",
	"sibur", "mendiane", "phiras", "thystame"}),
  _ptrNextAction({std::pair<std::string, bool (AI::*)(std::string const&)>("ok\n", &AI::computeNextAction),
	std::pair<std::string, bool (AI::*)(std::string const&)>("ko\n", &AI::actionError),
	std::pair<std::string, bool (AI::*)(std::string const&)>("mort\n", &AI::dead),
	std::pair<std::string, bool (AI::*)(std::string const&)>("elevation en cours\n", &AI::evolving),
	std::pair<std::string, bool (AI::*)(std::string const&)>("niveau actuel", &AI::incantation2),
    }),
  _actionPtr({&AI::forward, &AI::right, &AI::left, &AI::look, &AI::inventory, &AI::take, &AI::drop, &AI::expulse, &AI::broadcast, &AI::incantation, &AI::fork, &AI::slot}),
  _actions({"voir"}),
  _types({LOOK}),
  _pf(map) {}

AI::~AI() {

}

AI::AI(AI const & rhs) : _player(rhs._player), _map(rhs._map), _actions(rhs._actions), _pf(rhs._pf) {

}

AI & AI::operator=(AI const & rhs) {
  if (&rhs != this) {
    _actions = rhs._actions;
  }
  return *this;
}

bool			AI::updateData(std::string const &data) {
  if (_types.front() == AI::LOOK) {
    _map.update(data, _player.getPos(), _player.getDir(), _player.getLevel());
  }
  return computeNextAction(data);
}

bool			AI::computeNextAction(std::string const &data UNUSED) {
  return (this->*_actionPtr[_types.front()])();
}

bool			AI::evolving(std::string const &data UNUSED) {
  return false;
}

bool			AI::dead(std::string const &data UNUSED) {
  std::cout << "Dead" << std::endl;
  return false;
}

bool			AI::actionError(std::string const &data UNUSED) {
  addAction(LOOK);
  return true;
}

#include <cstring>
bool			AI::computeAction(std::string const & data) {
  std::vector<std::pair<std::string, bool (AI::*)(std::string const&)> >::iterator it = _ptrNextAction.begin();

  if (data.empty())
    return true;
  for (; it != _ptrNextAction.end(); ++it) {
    if (!strncmp(it->first.c_str(), data.c_str(), it->first.size()))
      return (this->*it->second)(data);
  }
  return updateData(data);
}

std::string const &	AI::getAction() const {
  return _actions.front();
}

void			AI::addAction(AI::actionType action, std::string const text) {
  _actions.push_front(text);
  _types.push_front(action);
  if (_actions.size() > 10) {
    _actions.pop_back();
    _types.pop_back();
  }
}

void			AI::addAction(AI::actionType action) {
  _actions.push_front(_typeText[action]);
  _types.push_front(action);
  if (_actions.size() > 10) {
    _actions.pop_back();
    _types.pop_back();
  }
}

void			AI::addAction(PathFinding::MoveInstruction action) {
  _actions.push_front(_typeText[action]);
  _types.push_front((actionType)action);
  if (_actions.size() > 10) {
    _actions.pop_back();
    _types.pop_back();
  }
}

void			AI::moveToPos(std::pair<int, int> const &) {
  addAction(FORWARD);
}

void			AI::explore() {
  if (_pf.isEmpty()) {
  std::pair<int, int> tmp((_player.getPos().first + 2) % _map.getWidth(), _player.getPos().second);
    _pf.computeNextPos(_player, tmp);
    addAction(LOOK);
  }
  else
    addAction(_pf.getNextInstruction());
}

void			AI::pickAll() {
  for (int i = 1; i < 8; ++i)
    if (_map.getTiles()[_player.getPos()][i] > 0) {
      _object = i - 1;
      addAction(PICK, _typeText[PICK] + std::string(_typeObjects[i - 1]));
      return;
    }
}

void			AI::pickObject(int i) {
  _object = i;
  addAction(PICK, _typeText[PICK] + std::string(_typeObjects[i]));
}

void			AI::dropObject(int i) {
  _object = i;
  addAction(DROP, _typeText[DROP] + std::string(_typeObjects[i]));
}

void			AI::checkForGems() {
  std::pair<int, int> gemPos;
  std::pair<int, int> errPos(6, 6);

  if ((gemPos = _map.gemNearPlayer(5, _player.getRequirement())) != errPos) {
    _pf.computeNextPos(_player, gemPos);
    if (_pf.isEmpty() == false)
      addAction(_pf.getNextInstruction());
    else {
      std::vector<int> required = _player.getIncant();
      for (int i = 1; i < 8; ++i)
	if (_player.getInv()[i] + _map.getTiles()[_player.getPos()][i] < required[i]) {
	  pickAll();
	  explore();
	  return;
	}
      for (int i = 1; i < 8; ++i) {
	if (_map.getTiles()[_player.getPos()][i] > required[i]) {
	  pickObject(i - 1);
	  return;
	}
	else if (_map.getTiles()[_player.getPos()][i] < required[i]) {
	  dropObject(i - 1);
	  return;
	}
	}
      tryToEvolve();
    }
  }
  else {
    explore();
  }
}

void			AI::checkPlayerFood() {
  if (_player.hasEnoughFood(5)) {
    checkForGems();
  }
  else {
    std::pair<int, int> tmp(_player.getPos().first + 2, _player.getPos().second);
    _pf.computeNextPos(_player, tmp);
    addAction(_pf.getNextInstruction());
  }
}

void			AI::evolve() {
}

void		      AI::tryToEvolve() {
  if (_player.canEvolve()) {
    ;
  }
  else {
    checkForGems();
  }
}

bool                  AI::forward(void) {
  _player.moveForward();
  _pf.popLastPos();
  if (!_pf.isEmpty()) {
    addAction(_pf.getNextInstruction());
  }
  else
    checkPlayerFood();
  return true;
}

bool                  AI::right(void) {
  _player.turnRight();
  if (!_pf.isEmpty()) {
    _pf.popLastPos();
  }
  if (!_pf.isEmpty()) {
    addAction(_pf.getNextInstruction());
  }
  return true;
}

bool                  AI::left(void) {
  _player.turnLeft();
  if (!_pf.isEmpty()) {
  _pf.popLastPos();
  }
  if (!_pf.isEmpty()) {
    addAction(_pf.getNextInstruction());
  }

  return true;
}

bool                  AI::look(void) {
  checkPlayerFood();
  return true;
}

bool                  AI::inventory(void) {
  look();
  return true;
}

bool                  AI::take(void) {
  _player.addItem(_object);
  checkPlayerFood();
  return true;
}

bool                  AI::drop(void) {
  _player.deleteItem(_object);
  return true;
}

bool                  AI::expulse(void) {
  return true;
}

bool                  AI::broadcast(void) {
  return true;
}

bool                  AI::incantation(void) {
  checkPlayerFood();
  return true;
}

bool                  AI::incantation2(std::string const &data) {
  _player.setLevel(std::atoi(data.substr(16).c_str()));
  return true;
}

bool                  AI::fork(void) {
  checkPlayerFood();
  return true;
}

bool                  AI::slot(void) {
  return true;
}
