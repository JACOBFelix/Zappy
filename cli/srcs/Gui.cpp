#include <iostream>
#include <sstream>
#include <string>
#include "Gui.hpp"
#include "Exceptions.hpp"

Gui::Gui(Player& player, Map & map, bool gui) : _player(player), _map(map) {
  /* Initial position of the player & game loop */
  _Loop = 0;
  _Open = true;
  _NoGui = false;
  if (!gui)
  {
    _Open = false;
    _NoGui = true;
    return;
  }

  /* Creating the window */
  if (SDL_Init(SDL_INIT_EVERYTHING) || TTF_Init())
    throw DisplayException("Could not initialize SDL");
  SDL_WM_SetCaption("Zappy", NULL);
  _Window = SDL_SetVideoMode(1440, 900, 32, SDL_SWSURFACE);
  if (_Window == NULL)
    throw DisplayException("Could not open window");

  /* Loading the font */
  _Font = TTF_OpenFont("./assets/fonts/filxgirl.ttf", 30);
  if (!_Font)
    throw DisplayException("Could not load font");
  _Black.r = 0;
  _Black.g = 0;
  _Black.b = 0;

  /* Misc texture loading */
  _Inventory = IMG_Load("./assets/UI/inventaire.png");
  _PlayerInfo = IMG_Load("./assets/UI/player_info.png");
  _Tile = IMG_Load("./assets/tiles/tile.png");
  _Egg = IMG_Load("./assets/characters/egg.png");
  _FXEvo = IMG_Load("./assets/FX/fx_evo.png");

  /* Loading the stones' textures */
  for (int i = 0; i < 7; i++) {
    SDL_Surface *Rock;
    std::stringstream ss;
    ss << "./assets/stones/caillou" << i << ".png";
    std::string str;
    ss >> str;
    Rock = IMG_Load(str.c_str());
    if (!Rock)
      throw DisplayException("Could not load rock texture");
    _Rocks.push_back(Rock);
  }

  /* Loading the ponies' textures */
  /* For each pony we load one position */
  for (int i = 0; i < 8; i++) {
    SDL_Surface *Pony;
    std::stringstream ss;
    ss << "./assets/characters/pony_" << i + 1 << ".png";
    std::string str;
    ss >> str;
    Pony = IMG_Load(str.c_str());
    if (!Pony)
      throw DisplayException("Could not load pony texture");
    _Ponies.push_back(Pony);
  }

  if (strlen(SDL_GetError()) > 0)
    throw DisplayException("Could not load images");
}

Gui::Gui(Gui const& rhs) : _player(rhs._player), _map(rhs._map) {}

Gui::~Gui() {}

Gui& Gui::operator=(Gui const& rhs) {
  if (this != &rhs) {
    _player = rhs._player;
    _map = rhs._map;
  };
  return *this;
}

void Gui::DrawUI() {
  /* Drawing the player informations & displaying it */
  DrawImage(0, 0, _PlayerInfo, true);
  DrawPony(-13000, -13000, true);
  std::stringstream ss;
  ss << _player.getTeamName() << " lv " << _player.getLevel();
  std::string str;
  ss >> str;
  SDL_Surface *descr = TTF_RenderText_Solid(_Font, str.c_str(), _Black);
  if (!descr)
    throw DisplayException("Could not write text");
  DrawImage(110000, 0, descr, true);

  /* Drawing the inventory and displaying its content */
  DrawImage(740000, 700000, _Inventory, true);
  descr = TTF_RenderText_Solid(_Font, " Nourriture   Linemate Deraumere    Sibur    Mendiane    Phiras    Thystame", _Black);
  DrawImage(740000, 820000, descr, true);
  char phrase[256] = "\0";
  sprintf(phrase, "%8d%13d%14d%13d%14d%14d%13d", _player.getInv()[0], _player.getInv()[1], _player.getInv()[2], _player.getInv()[3], _player.getInv()[4], _player.getInv()[5], _player.getInv()[6]);
  descr = TTF_RenderText_Solid(_Font, phrase, _Black);
  DrawImage(740000, 850000, descr, true);
}

void Gui::ClearGUI() {
  std::vector<SDL_Surface*>::iterator it;
  for (it = _Rocks.begin(); it != _Rocks.end(); it++)
    SDL_FreeSurface(*it);
  _Rocks.clear();
  for (it = _Ponies.begin(); it != _Ponies.end(); it++)
    SDL_FreeSurface(*it);
  _Ponies.clear();

  SDL_FreeSurface(_Inventory);
  SDL_FreeSurface(_PlayerInfo);
  SDL_FreeSurface(_Tile);
  SDL_FreeSurface(_Egg);
  SDL_FreeSurface(_FXEvo);
  SDL_Quit();
}

void		Gui::update() {
  while (_Open) {
    while (SDL_PollEvent(&_Event)) {
      if (_Event.key.keysym.sym == SDLK_ESCAPE)
        _Open = false;
    }
    DrawMap();
    DrawUI();
    if (SDL_Flip(_Window) == -1)
      throw DisplayException("Error during display");
    _Loop++;
  }
  if (!_NoGui)
    ClearGUI();
}

void Gui::DrawPony(int x, int y, bool pc) {
  SDL_Rect rect;
  SDL_Rect coord;

  coord.x = (float)x / 1000;
  coord.y = (float)y / 1000;
  if (pc) {
    rect.x = 0;
    rect.y = _player.getDir() >= 3 ? 0 : 126;
  }
  else {
    rect.x = 0;
    rect.y = 0;
  }
  rect.w = 126;
  rect.h = 126;
  if (pc) {
    if (SDL_BlitSurface(_Ponies[_player.getLevel() - 1], &rect, _Window, &coord) != 0)
      throw DisplayException("Could not display the pony :(");
  }
  else {
    if (SDL_BlitSurface(_Ponies[0], &rect, _Window, &coord) != 0)
      throw DisplayException("Could not display the pony :(");
  }
}

void Gui::DrawImage(int x, int y, SDL_Surface *img, bool InFOV) {
  if (!InFOV)
    SDL_SetAlpha(img, SDL_SRCALPHA, 100);
  else
    SDL_SetAlpha(img, SDL_SRCALPHA, 255);
  SDL_Rect Coord;
  Coord.x = (float)x / 1000;
  Coord.y = (float)y / 1000;
  if (SDL_BlitSurface(img, NULL, _Window, &Coord) != 0)
    throw DisplayException("Could not display image");
}

void Gui::DrawAnimation(int x, int y, SDL_Surface *img, SDL_Surface *img2) {
  if (_Loop % 100 < 50)
    DrawImage(x, y, img, true);
  else
    DrawImage(x, y, img2, true);
}

void Gui::DrawTile(int x, int y) {
  int i, j, i_, j_, tmpi, tmpj;
  tmpi = x + _player.getPos().first - 5;
  i_ = (tmpi >= 0) ? (tmpi % _map.getWidth()) : ((tmpi + _map.getWidth() * (-tmpi / _map.getWidth() + 1)) % _map.getWidth());
  tmpj = y + _player.getPos().second - 4;
  j_ = (tmpj >= 0) ? (tmpj % _map.getHeight()) : ((tmpj + _map.getHeight() * (-tmpj / _map.getHeight() + 1)) % _map.getHeight());
  i = x * 1000 - _player.getPos().first % 1000;
  j = y * 1000 - _player.getPos().second % 1000;

  std::map<std::pair<int, int>, Tile>::iterator it;
  for (it = _map.getTiles().begin(); it != _map.getTiles().end(); it++) {
    if (it->first.first == i_ && it->first.second == j_) {
      DrawImage(i * 126, j * 100, _Tile, true);
      for (int n = 0; n < 7; n++) {
	if (it->second[n] > 0) {
	  DrawImage(i * 126, j * 100 + 10000, _Rocks[n], true);
	}
      }
    }
  }
}

void Gui::DrawMap() {
  SDL_FillRect(_Window, NULL, 0x00);
  for (int i = 0; i < 15; i++) {
  	for (int j = 0; j < 10; j++) {
		DrawTile(i, j);
  	}
  }
  DrawPony(5000 * 126, 4000 * 100 - 10000, true);
}
