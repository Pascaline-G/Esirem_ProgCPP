#ifndef H_SUDOKU_
#define H_SUDOKU_

#include <array>
#include <cstdint>
#include <iostream>

class Sudoku
{
public:
    Sudoku(uint8_t difficulty = 3);
    
    bool isLineValid(size_t line, int value)  const;
    bool isColValid(size_t column, int value) const;
    bool isSquareValid(size_t line, size_t column, int value) const;
    bool isPlacementValid(size_t line, size_t column, int value) const;

    void solve();

private:
    bool solve(size_t line, size_t column);

    std::array<int,9*9> _grid;
    uint8_t _difficulty;

friend std::ostream& operator<<(std::ostream& os, const Sudoku& sudoku);
};

#endif //!H_SUDOKU_