#include "sudoku.h"
#include <iostream>

int main() {
  Sudoku s(5);
  std::cout << s << std::endl;

  bool success = s.solve();

  std::cout << (success ? "success" : "unable to solve sudoku") << std::endl;
  std::cout << s << std::endl;

  return 0;
}