#pragma once
#include "../cppfiles/Cell.cpp"

class Board {
  Cell board_[constants::board_size][constants::board_size];
 public:
  void PutShip(Ship* ship, std::pair<int, int> starting_point, bool is_vertical);
  bool AllShipsDead();
  Cell& GetCell(std::pair<int, int> coord);
};