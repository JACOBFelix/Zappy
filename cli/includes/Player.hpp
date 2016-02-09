#pragma once

#include <utility>
#include <vector>
#include <string>

#define INCANT_NBR 7
#define LEVEL_MAX 8

class Map;

class Player {
public:
  enum direction {NORTH, EAST, SOUTH, WEST};

private:
  int _width;
  int _height;
  int _food;
  int _level;
  direction _dir;
  std::pair<int, int> _pos;

  std::vector<int> _inv;
  std::vector<bool> _requirement;
  std::vector<std::vector<int> > _incant;
  std::vector<std::pair<int, int> > _moveTab;
  std::string _teamName;

public:
  Player(int const w, int const h, std::string const& teamName);
  ~Player();
  Player(Player const &);
  Player & operator=(Player const &);

  bool		hasEnoughFood(int);

  int	getLevel(void) const;
  void setLevel(int const);
  bool		canEvolve();
  void		moveForward(void);
  std::pair<int, int> const &		getPos(void) const;

  void			turnLeft(void);
  void			turnRight(void);
  void			takeObject();
  direction const &	getDir(void) const;

  std::vector<int> const & getInv(void) const;

  std::vector<int> const & getIncant(void) const;

  std::vector<bool> const & getRequirement(void) const;
  void			setRequirement(int, bool);

  void			deleteItem(int);
  void			addItem(int);

  int& getWidth(void);
  void setWidth(int const w);
  int& getHeight(void);
  void setHeight(int const h);

  std::string const& getTeamName(void) const;
};
