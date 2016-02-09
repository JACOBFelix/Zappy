#pragma once

#include <vector>

class Tile {
private:
  std::vector<int> _elements;

public:
  Tile();
  ~Tile();
  Tile(Tile const& rhs);
  Tile& operator=(Tile const& rhs);

  int& operator[](int const i);

  std::vector<int> const& getElements(void) const;
  int& getElement(int const i);

  void setElement(int const i, int const value);
};
