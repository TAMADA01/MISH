#include <iostream>

#include <vector>
#include "src/figures/abstract_figure.h"
#include "src/figures/impls/rectangle.h"

void test();

int main() {
  std::vector<Figure *> figures;

  figures.push_back( new Rectangle("Test1", 10, 15));
  figures.push_back( new Rectangle("Test2", 9, 26));
  figures.push_back( new Rectangle("Test3", 65, 12));

  for (int i = 0; i < figures.size(); ++i) {
    std::cout << "#" << (i+1) << "\t" << figures[i]->Info() << std::endl;
  }
  return 0;
}

void test(){

  std::cout << "Hello, World!" << std::endl;
}
