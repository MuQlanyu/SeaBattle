#pragma once
#include "../headers/Board.h"

void Board::PutShip(Ship* ship, std::pair<int, int> starting_point, bool is_vertical) {
  for (size_t i = 0; i <= ship->Length(); ++i) {
    if (is_vertical) {
      board_[starting_point.first][starting_point.second + i].SetType(ship_cell, ship);
    } else {
      board_[starting_point.first + i][starting_point.second].SetType(ship_cell, ship);
    }
  }
}

bool Board::AllShipsDead() {
  for (size_t i = 0; i < constants::board_size; ++i) {
    for (size_t j = 0; j < constants::board_size; ++j) {
      if (board_[i][j].GetType() == ship_cell && board_[i][j].IsAlive()) {
        return false;
      }
    }
  }
  return true;
}

Cell& Board::GetCell(std::pair<int, int> coord) {
  return board_[coord.first][coord.second];
}

int AddBits(int number, std::vector<int> index) {
  return number | (1 << index[0]) | (1 << index[1]) | (1 << index[2]);
}

//0 1 2
//3 4 5 Нумерация клеток вокруг
//6 7 8
int CheckSurroundings(int x, int y) {
  int cell_choose = 0;
  if (x == 0) cell_choose = AddBits(cell_choose, {0, 3, 6});
  if (y == 0) cell_choose = AddBits(cell_choose, {0, 1, 2});
  if (x == constants::board_size - 1) cell_choose = AddBits(cell_choose, {2, 5, 8});
  if (y == constants::board_size - 1) cell_choose = AddBits(cell_choose, {6, 7, 8});
  return cell_choose;
}

void ShootAround(Board* board, int x, int y) {
  int cell_choose = CheckSurroundings(x, y);
  for (size_t i = 0; i < 9; ++i) {
    if ((cell_choose & (1 << i)) == 0) {
      board->GetCell({x - 1 + (i % 3), y - 1 + (i / 3)}).IsShoot();
    }
  }
}

void Ship::DecreaseLives() {
  --number_lives_;
  if (number_lives_ == 0) {
    for (size_t i = 0; i <= Length(); ++i) {
      if (IsVertical()) {
        ShootAround(board_, starting_point_.first, starting_point_.second + i);
      } else {
        ShootAround(board_, starting_point_.first + i, starting_point_.second);
      }
    }
  }
}