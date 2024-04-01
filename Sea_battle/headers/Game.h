#pragma once
#include <vector>
#include "../cppfiles/Board.cpp"
#include "Facade.h"

class Game {
  int number_of_players;
  int number_deaths = 0;
  std::vector<bool> dead_players;
  Player player_[constants::players_number];
  size_t turn_ = 0;
  Board boards_[constants::players_number];
  bool gameover_ = false;
  Facade* facade_ = new ConsoleApplication;

  void TryShoot(int number_opponent);
 public:
  Game();
  void PutShips(std::vector<Ship>& ships);
  void MakeShoot(int number_opponent);
  void GameLoop();
};
