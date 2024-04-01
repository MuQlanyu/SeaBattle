#pragma once
#include "../cppfiles/Ship.cpp"

class Cell {
  bool is_alive_ = true;
  CellType cell_type_ = simple;
  Ship* ship_ = nullptr;
  char image_[2] = {'~', simple}; // image[0] -
 public:
  void IsShoot();
  void SetType(CellType type, Ship* ship = nullptr);
  CellType GetType();
  char GetImage(bool is_hidden);
  bool IsAlive();
};