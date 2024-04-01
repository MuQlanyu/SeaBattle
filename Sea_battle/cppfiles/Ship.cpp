#pragma once
#include "../headers/Ship.h"

bool Ship::IsVertical() {
  return starting_point_.first == ending_point_.first;
}

void Ship::SetLife(size_t number_lives) {
  number_lives_ = number_lives;
}

void Ship::SetShip(std::pair<int, int> start, std::pair<int, int> end, Board* board) {
  starting_point_ = start;
  ending_point_ = end;
  board_ = board;
}

size_t Ship::Length() {
  return abs(starting_point_.first - ending_point_.first) +
      abs(starting_point_.second - ending_point_.second);
}

std::pair<int, int>& Ship::GetStart() {
  return starting_point_;
}

std::pair<int, int>& Ship::GetEnd() {
  return ending_point_;
}

char Ship::GetOrient() {
  if (IsVertical()) return 'v';
  return 'h';
}