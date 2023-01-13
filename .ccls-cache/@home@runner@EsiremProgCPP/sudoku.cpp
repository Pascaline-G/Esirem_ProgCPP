#include "sudoku.h"
#include <cmath>
#include <cstdlib>
#include <ctime>

Sudoku::Sudoku(uint8_t difficulty, uint8_t lineSize)
    : _grid(), _difficulty(difficulty), _lineSize(lineSize) {

  // check if _lineSize is a perfect square
  _lineSize = std::pow(std::round(std::sqrt(_lineSize)), 2);

  for (size_t i = 0; i < _lineSize; i++) {
    for (size_t j = 0; j < _lineSize; j++) {
      _grid.push_back(0);
    }
  }
  std::srand(std::time(nullptr));

  difficulty = difficulty > 5 ? 5 : difficulty;

  const double nbCases = _lineSize * _lineSize;
  size_t nbCaseToFill = 0;
  switch (difficulty) {
  case 1:
    nbCaseToFill = nbCases * 0.45;
    break;
  case 2:
    nbCaseToFill = nbCases * 0.40;
    break;
  case 3:
    nbCaseToFill = nbCases * 0.35;
    break;
  case 4:
    nbCaseToFill = nbCases * 0.30;
    break;
  case 5:
    nbCaseToFill = nbCases * 0.20;
    break;
  default:
    break;
  }

  for (size_t i = 0; i < nbCaseToFill; i++) {
    int value = (std::rand() % _lineSize) + 1;
    size_t x = std::rand() % _lineSize;
    size_t y = std::rand() % _lineSize;

    while (_grid.at(x * _lineSize + y) != 0 || !isPlacementValid(x, y, value)) {
      value = (std::rand() % _lineSize) + 1;
      x = std::rand() % _lineSize;
      y = std::rand() % _lineSize;
    }
    _grid.at(x * _lineSize + y) = value;
  }
}

std::ostream &operator<<(std::ostream &os, const Sudoku &sudoku) {
  int squareSize = (int)std::sqrt(sudoku._lineSize);
  auto displayLine = [squareSize, sudoku](std::ostream &os) -> void {
    os << "+";
    for (int i = 0; i < squareSize; i++) {
      for (int j = 0; j < (squareSize * 2 + 1); j++) {
        os << "-";
      }
      os << "+";
    }
  };

  displayLine(os);
  os << std::endl;
  for (std::uint8_t i = 0; i < sudoku._lineSize; i++) {
    for (std::uint8_t j = 0; j < sudoku._lineSize; j++) {
      if (j == 0 || j % squareSize == 0) {
        os << "| ";
      }

      if (sudoku._grid.at(i * sudoku._lineSize + j) == 0) {
        os << '.';
      } else {
        os << sudoku._grid.at(i * sudoku._lineSize + j);
      }
      os << " ";

      if (j == sudoku._lineSize - 1) {
        os << "|";
      }
    }
    if ((i + 1) % squareSize == 0) {
      os << std::endl;
      displayLine(os);
    }
    os << std::endl;
  }
  return os;
}

bool Sudoku::isLineValid(size_t line, int value) const {
  for (size_t i = 0; i < _lineSize; i++) {
    if (_grid.at(_lineSize * line + i) == value) {
      return false;
    }
  }
  return true;
}

bool Sudoku::isColValid(size_t column, int value) const {
  for (size_t i = 0; i < _lineSize; i++) {
    if (_grid.at(i * _lineSize + column) == value) {
      return false;
    }
  }
  return true;
}

bool Sudoku::isSquareValid(size_t line, size_t column, int value) const {
  int squareSize = (int)std::sqrt(_lineSize);
  const size_t gauche = (line / squareSize) * squareSize;
  const size_t haut = (column / squareSize) * squareSize;

  for (size_t i = gauche; i < gauche + squareSize; i++) {
    for (size_t j = haut; j < haut + squareSize; j++) {
      if (_grid.at(i * _lineSize + j) == value) {
        return false;
      }
    }
  }
  return true;
}

bool Sudoku::isPlacementValid(size_t line, size_t column, int value) const {
  if (value > _lineSize) {
    return false;
  }
  if (line >= _lineSize || column >= _lineSize) {
    return false;
  }
  return isLineValid(line, value) && isColValid(column, value) &&
         isSquareValid(line, column, value);
}

bool Sudoku::solve() { return solve(0, 0); }

bool Sudoku::solve(int line, int column) {
  // check if we are at the last square (sudoku solved)
  if (line == _lineSize - 1 && column == _lineSize)
    return true;

  // pass to the next line at the end of it
  if (column == _lineSize) {
    line++;
    column = 0;
  }

  // pass to the next square if this is already done
  if (_grid.at(line * _lineSize + column) > 0)
    return solve(line, column + 1);

  // for each possible value [1 - _lineSize]
  for (int value = 1; value <= _lineSize; value++) {
    // check if the solution is possible
    if (isPlacementValid(line, column, value)) {
      _grid.at(line * _lineSize + column) = value;

      // std::cout << *this << std::endl;

      // continue in this solution
      if (solve(line, column + 1)) {
        return true;
      }
    }

    // if the solution is not possible reset it
    _grid.at(line * _lineSize + column) = 0;
  }

  return false;
}
