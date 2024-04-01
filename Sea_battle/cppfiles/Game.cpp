#pragma once
#include "../headers/Game.h"

Game::Game() {
  dead_players.resize(constants::players_number, false);
  facade_->DrawText("Введите количество игроков от 2 до 8:\n");
  std::cin >> number_of_players;
}

bool IsFree(Board& board, int x, int y) {
  int cell_choose = CheckSurroundings(x, y);
  for (size_t i = 0; i < 9; ++i) {
    if ((cell_choose & (1 << i)) == 0) {
      if (board.GetCell({x - 1 + (i % 3), y - 1 + (i / 3)}).GetType() == ship_cell) {
        return false;
      }
    }
  }
  return true;
}

bool PointInBoarders(std::pair<int, int> point) {
  if (point.first < 0 || point.first >= constants::board_size) return false;
  if (point.second < 0 || point.second >= constants::board_size) return false;
  return true;
}

bool IsPlaceable(Board& board, std::pair<int, int> start, size_t size, bool is_vertical) {
  std::pair<int, int> end = start;
  if (is_vertical) end.second += size;
  else end.first += size;
  if (!PointInBoarders(start) || !PointInBoarders(end)) return false;
  for (size_t i = 0; i <= size; ++i) {
    if (is_vertical) {
      if (!IsFree(board, start.first, start.second + i)) return false;
    } else {
      if (!IsFree(board, start.first + i, start.second)) return false;
    }
  }
  return true;
}

void ClearConsole() {
  std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

void Game::PutShips(std::vector<Ship>& ships) {
  try {
    Ship* fake_ship;
    size_t ship_index = 0;
    for (size_t turn = 0; turn < number_of_players; ++turn) {
      facade_->DrawText(player_[turn].GetName() + " расставьте свои корабли\n");
      for (size_t ship_size = 0; ship_size < constants::ships.size(); ++ship_size) {
        for (size_t ship_number = 0; ship_number < constants::ships[ship_size]; ++ship_number) {
          facade_->DrawMyBoard(boards_[turn]);
          fake_ship->GetStart() = {-1, -1};
          while (!IsPlaceable(boards_[turn], fake_ship->GetStart(),
                              ship_size, fake_ship->GetOrient() == 'v')) {
            facade_->DrawText("Введите координаты начальной точки и его ориентацию(v/h)\n"
                              " Размер корабля: " + std::to_string(ship_size + 1) + "\n");
            facade_->GetShip(fake_ship, ship_size);
          }
          ships[ship_index].SetShip(fake_ship->GetStart(), fake_ship->GetEnd(), &boards_[turn]);
          boards_[turn].PutShip(&ships[ship_index++], fake_ship->GetStart(), fake_ship->GetOrient() == 'v');
          facade_->ClearScreen();
        }
      }
    }
  } catch (...) {
    std::cout << "LOL";
  }
}

void Game::TryShoot(int number_opponent) {
  try {
    facade_->ClearScreen();
    facade_->DrawTwoBoards(boards_[number_opponent], boards_[turn_]);
    facade_->DrawText("Введите координаты выстрела: ");
  } catch (...) {
    std::cout << "HAHA";
  }

}

void Game::MakeShoot(int number_opponent) {
  std::pair<int, int> coords;
  TryShoot(number_opponent);
  coords = facade_->GetShoot();
  while (!PointInBoarders(coords) || !boards_[number_opponent].GetCell(coords).IsAlive()) {
    TryShoot(number_opponent);
    coords = facade_->GetShoot();
    facade_->DrawText("\n");
  }
  boards_[number_opponent].GetCell(coords).IsShoot();
  if (boards_[number_opponent].AllShipsDead()) {
    ++number_deaths;
    dead_players[number_opponent] = true;
    if (number_deaths == number_of_players - 1) {
      gameover_ = true;
    }
    facade_->DrawText("Ты убил своего соперника\n Ход переходит следующему игроку");
    return;
  }
  facade_->ClearScreen();
  if (boards_[number_opponent].GetCell(coords).GetType() == ship_cell) {
    facade_->DrawText("Вы попали\n");
    this->MakeShoot(number_opponent);
  } else {
    facade_->DrawTwoBoards(boards_[number_opponent], boards_[turn_]);
    facade_->DrawText("Вы не попали\n");
  }
}

void Game::GameLoop() {
  std::vector<Ship> ships;
  for (size_t turn = 0; turn < number_of_players; ++turn) {
    for (size_t ship_size = 0; ship_size < constants::ships.size(); ++ship_size) {
      for (size_t ship_number = 0; ship_number < constants::ships[ship_size]; ++ship_number) {
        Ship new_ship;
        new_ship.SetLife(ship_size + 1);
        ships.push_back(new_ship);
      }
    }
  }
  PutShips(ships);
  gameover_ = false;
  turn_ = 0;
  std::string password;
  while (!gameover_) {
    password = "";
    while (player_[turn_].GetPassword() != password) {
      facade_->DrawText(player_[turn_].GetName() + "введите пароль: ");
      password = facade_->GetPassword(player_[turn_]);
    }
    facade_->ReadyToShoot();
    if (number_of_players > 2) {
      char number_opponnent = 0;
      while (number_opponnent - '0' <= 0 ||
          number_opponnent - '0' > number_of_players ||
          number_opponnent - '0' == turn_ + 1 ||
          dead_players[number_opponnent - '0']) {
        std::cout << "Введите номер игрока от 1 до " << number_of_players << '\n';
        std::cin >> number_opponnent;
      }
      int num = number_opponnent - '0';
      --num;
      MakeShoot(num);
      turn_ = (turn_ + 1) % number_of_players;
    } else {
      int num = (turn_ + 1) % 2;
      MakeShoot(num);
      turn_ = (turn_ + 1) % number_of_players;
    }
  }
}