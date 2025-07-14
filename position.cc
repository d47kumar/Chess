#include "position.h";

Position::Position(int row, int column, bool occupied) : row{row}, column{column}, occupied{occupied} {};

bool Position::isValid() const {
    if (occupied) { return false; }
    
    return (row >= 0) && (row <= 7) && (column >= 0) && (column <= 7);
} // Position::isValid

int Position::getRow() const {
    return row;
} // Position::getRow

int Position::getColumn() const {
    return column;
} // Position::getColumn
