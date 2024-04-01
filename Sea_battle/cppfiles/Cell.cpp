#include "../headers/Cell.h"

void Cell::IsShoot() {
  if (!is_alive_) return;
  is_alive_ = false;
  image_[0] = cell_type_;
  if (cell_type_ == ship_cell) {
    ship_->DecreaseLives();
  }
}

void Cell::SetType(CellType type, Ship* ship) {
  cell_type_ = type;
  image_[1] = cell_type_;
  if (cell_type_ == ship_cell) {
    ship_ = ship;
  }
}

CellType Cell::GetType() {
  return cell_type_;
}

char Cell::GetImage(bool is_hidden) {
  if (is_hidden) return image_[0];
  return image_[1];
}

bool Cell::IsAlive() {
  return is_alive_;
}