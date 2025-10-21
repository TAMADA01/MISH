#include "rectangle.h"
#include <cmath>

Rectangle::Rectangle(const std::string &name, int wight, int height) : Figure(name) {
  _wight = wight;
  _height = height;
}

std::string Rectangle::Info() {
  return getName() + ": width = " + std::to_string(_wight) + " height = " + std::to_string(_height);
}

double Rectangle::getPerimeter() {
  return 0;
}

double Rectangle::getArea() {
  return 0;
}

