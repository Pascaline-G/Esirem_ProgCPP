#include "sudoku.h"

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