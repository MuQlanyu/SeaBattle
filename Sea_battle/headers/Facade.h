#pragma once
#include "Board.h"
#include "../cppfiles/Player.cpp"

class Facade {
 public:
  virtual void DrawMyBoard(Board& board) {}
  virtual void DrawOpponentBoard(Board& board) {}

  virtual void DrawText(const std::string& message) {}
  virtual void ClearScreen() {}

  virtual void SetName(Player& player) {}
  virtual void SetPassword(Player& player) {}
  virtual void DrawTwoBoards(Board& first, Board& second) {}
  
  virtual std::string GetName(Player& player) {}
  virtual std::string GetPassword(Player& player) {}

  virtual Ship* GetShip(Ship* ship, size_t length) {}
  virtual std::pair<int, int> GetShoot() {}
  virtual void ReadyToShoot() {}
};

class ConsoleApplication : public Facade {
 public:
  void DrawBoard(Board& board, bool is_hidden) {
    std::cout << "  ";
    for (size_t i = 0; i < constants::board_size; ++i) {
      std::cout << ' ' << i ;
    }
    std::cout << "\n\n";
    for (size_t i = 0; i < constants::board_size; ++i) {
      std::cout << i << ' ';
      for (size_t j = 0; j < constants::board_size; ++j) {
        std::cout << ' ' << board.GetCell({j, i}).GetImage(is_hidden);
      }
      std::cout << '\n';
    }
  }

  void DrawTwoBoards(Board& first, Board& second) override {
    bool first_is_hidden = true;
    bool second_is_hidden = false;
    std::cout << "  ";
    for (size_t i = 0; i < constants::board_size; ++i) {
      std::cout << ' ' << i ;
    }
    std::cout << "   |   ";
    for (size_t i = 0; i < constants::board_size; ++i) {
      std::cout << ' ' << i ;
    }

    std::cout << "\n\n";
    for (size_t i = 0; i < constants::board_size; ++i) {
      std::cout << i << ' ';
      for (size_t j = 0; j < constants::board_size; ++j) {
        std::cout << ' ' << first.GetCell({j, i}).GetImage(first_is_hidden);
      }
      std::cout << "   |   ";

      std::cout << i << ' ';
      for (size_t j = 0; j < constants::board_size; ++j) {
        std::cout << ' ' << second.GetCell({j, i}).GetImage(second_is_hidden);
      }
      std::cout << '\n';
    }
  }

  void DrawOpponentBoard(Board& board) override {
    DrawBoard(board, true);
  }

  void DrawMyBoard(Board& board) override {
    DrawBoard(board, false);
  }

  Ship* GetShip(Ship* ship, size_t length) override {
    char orientation;
    std::cin >> ship->GetStart().first >> ship->GetStart().second >> orientation;
    ship->GetEnd() = ship->GetStart();
    if (orientation == 'v') ship->GetEnd().second += length;
    else ship->GetEnd().first += length;
    return ship;
  }

  std::pair<int, int> GetShoot() override {
    std::pair<int, int> tmp;
    std::cin >> tmp.first >> tmp.second;
    return tmp;
  }

  void DrawText(const std::string& message) override {
    std::cout << message << '\n';
  }

  void ClearScreen() override {
    std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
  }

  void SetName(Player& player) override {
    std::string name;
    std::cout << "Введите имя: ";
    std::cin >> name;
    std::cout << '\n';
    player.SetName(name);
  }

  void SetPassword(Player& player) override {
    std::string password;
    std::cout << "Введите пароль: ";
    std::cin >> password;
    std::cout << '\n';
    player.SetPassword(password);
  }

  std::string GetName(Player& player) override {
    return player.GetName();
  }

  std::string GetPassword(Player& player) override {
    return player.GetPassword();
  }

  void ReadyToShoot() {
    ClearScreen();
    std::string s;
    std::cout << "Выготовы ходить?";
    std::cin >> s;
  }
};
