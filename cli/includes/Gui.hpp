#pragma once

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <vector>
#include "Map.hpp"
#include "Tile.hpp"
#include "Player.hpp"

class Gui {
private:
  Player& _player;
  Map& _map;

  int _Loop;
  bool _Open;
  bool _NoGui;
  SDL_Surface *_Window;
  SDL_Event _Event;
  TTF_Font *_Font;
  SDL_Surface *_Tile;
  SDL_Surface *_Egg;
  SDL_Surface *_FXEvo;
  SDL_Surface *_Inventory;
  SDL_Surface *_PlayerInfo;
  SDL_Color _Black;
  std::vector<SDL_Surface*> _Rocks;
  std::vector<SDL_Surface*> _Ponies;

public:
  Gui(Player&, Map &, bool);
  Gui(Gui const &rhs);
  ~Gui();
  Gui& operator=(Gui const &rhs);

  void update();
  void ClearGUI();
  void DrawMap();
  void DrawUI();
  void DrawTile(int, int);
  void DrawImage(int, int, SDL_Surface *, bool);
  void DrawAnimation(int, int, SDL_Surface *, SDL_Surface *);
  void DrawPony(int, int, bool);
};
