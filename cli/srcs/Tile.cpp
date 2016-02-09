#include "Tile.hpp"

Tile::Tile() : _elements(7, 0) {
}

Tile::~Tile() {}

Tile::Tile(Tile const& rhs) {
  _elements = rhs._elements;
}

Tile& Tile::operator=(Tile const& rhs) {
  if (this != &rhs) {
    _elements = rhs._elements;
  }
  return *this;
}

int& Tile::operator[](int const i) {
  return _elements[i];
}

std::vector<int> const& Tile::getElements(void) const {
  return _elements;
}

int& Tile::getElement(int const i) {
  return _elements[i];
}

void Tile::setElement(int const i, int const value) {
  _elements[i] = value;
}
