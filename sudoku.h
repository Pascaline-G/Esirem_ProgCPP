#ifndef H_SUDOKU_
#define H_SUDOKU_

#include <cstdint>
#include <iostream>
#include <vector>

class Sudoku {
public:
  Sudoku(uint8_t difficulty = 3, uint8_t lineSize = 9);

  bool isLineValid(size_t line, int value) const;
  bool isColValid(size_t column, int value) const;
  bool isSquareValid(size_t line, size_t column, int value) const;
  bool isPlacementValid(size_t line, size_t column, int value) const;

  bool solve();

private:
  bool solve(int line, int column);

  std::vector<int> _grid;
  uint8_t _difficulty;
  uint8_t _lineSize;

  friend std::ostream &operator<<(std::ostream &os, const Sudoku &sudoku);
};

#endif //! H_SUDOKU_