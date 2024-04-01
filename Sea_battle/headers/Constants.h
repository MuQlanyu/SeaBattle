#pragma once
#include <iostream>
#include <vector>

enum CellType : char {
  simple = '.',
  ship_cell = 'X'
};

namespace constants {
const size_t board_size = 10;
const size_t players_number = 9;
const std::vector<size_t> ships = {0, 0, 3};
}