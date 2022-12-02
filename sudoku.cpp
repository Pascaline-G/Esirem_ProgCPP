#include "sudoku.h"

Sudoku::Sudoku(uint8_t difficulty) : _grid(),_difficulty(difficulty)
{
}

std::ostream& operator<<(std::ostream& os, const Sudoku& sudoku)
{
    auto displayLine = [](std::ostream &os) -> void {
        os << "+-------+-------+-------+";
    };

    displayLine(os);
    os << std::endl;
    for (size_t i = 0; i < 9; i++)
    {
        for (size_t j = 0; j < 9; j++)
        {
            if(j == 0 || j % 3 == 0) {
                os << "| ";
            }

            if (sudoku._grid.at(i * 9 + j) == 0) {
                os << '.';
            } else {
                os << sudoku._grid.at(i * 9 + j);
            }
            os << " ";          

            if(j == 9 - 1) {
                os << "|";
            }
        }
        if((i + 1) % 3 == 0) {
            os << std::endl;
            displayLine(os);
        }
        os << std::endl;        
    }
    return os;
}


bool Sudoku::isLineValid(size_t line, int value)  const {
    for (size_t i = 0; i < 9; i++)
    {
        if(_grid.at(9 * line + i) == value){
            return false;
        }
    }
    return true;
}

bool Sudoku::isColValid(size_t column, int value) const {
    for (size_t i = 0; i < 9; i++)
    {
        if(_grid.at(i * 9 + column) == value){
            return false;
        }
    }
    return true;
}

bool Sudoku::isSquareValid(size_t line, size_t column, int value) const{
    const size_t gauche = (line / 3) * 3;
    const size_t haut = (column / 3) * 3;

    for (size_t i = gauche; i < gauche + 3; i++)
    {
        for (size_t j = haut; j < haut + 3; j++)
        {
            if(_grid.at(i * 9 + j) == value){
                return false;
            }
        }
        
    }
    return true;
}

bool Sudoku::isPlacementValid(size_t line, size_t column, int value) const {
    if(value > 9) {
        return false;
    }
    if(line >= 9 || column >= 9) {
        return false;
    }
    return isLineValid(line, value) 
        && isColValid(column, value) 
        && isSquareValid(line, column, value);
}

bool Sudoku::solve(size_t line, size_t column) {
    //check if we are at the last square (sudoku solved)
    if (line == _grid.size() - 1 && column == 9)
        return true;

    //pass to the next line at the end of it
    if (column == 9) {
        line++;
        column = 0;
    }

    //pass to the next square if this is already done
    if (_grid.at(line * 9 + column) > 0)
        return solve(line, column + 1);

    //for each possible value [1 - 9]
    for (int value = 1; value <= 9; value++)
    {
        //check if the solution is possible
        if (isPlacementValid(line, column, value)) 
        {
            _grid.at(line * 9 + column) = value;

            // std::cout << *this << std::endl;

            //continue in this solution 
            if (solve(line, column + 1)) {
                return true;
            }
        }

        //if the solution is not possible reset it
        _grid.at(line * 9 + column) = 0;
    }

    return false;
}
