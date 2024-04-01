#pragma once
#include "Constants.h"

class Board;

class Ship {
  size_t number_lives_;
  std::pair<int, int> starting_point_;
  std::pair<int, int> ending_point_;
  Board* board_ = nullptr;

  bool IsVertical();
 public:
  void SetLife(size_t number_lives);
  void SetShip(std::pair<int, int> start, std::pair<int, int> end, Board* board);
  size_t Length();
  void DecreaseLives();

  std::pair<int, int>& GetStart();
  std::pair<int, int>& GetEnd();
  char GetOrient();
};