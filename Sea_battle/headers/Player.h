#pragma once
#include <iostream>

class Player {
  std::string name_;
  std::string password_;
  size_t hits_ = 0;
 public:
  void SetName(std::string& name);
  std::string GetName();
  void SetPassword(std::string& password);
  std::string GetPassword();
  //Проверка на отсутствие пробелов в пароле
};
