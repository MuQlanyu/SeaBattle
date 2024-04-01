#include "../headers/Player.h"

void Player::SetName(std::string& name) {
  name_ = name;
}

std::string Player::GetName() {
  return name_;
}

void Player::SetPassword(std::string& password) {
  password_ = password;
}

std::string Player::GetPassword() {
  return password_;
}