#ifndef H_SUDOKU_
#define H_SUDOKU_

#include <array>
#include <cstdint>

class Sudoku
{
public:
    Soduku(uint8_t difficulty = 3);
    

private:
    std::array<int,9*9> _grid;
    uint8_t _difficulty;
};

#endif //!H_SUDOKU_