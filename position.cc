#include "position.h";

bool Position::isValid() const {
    return (row >= 0) && (row <= 7) && (column >= 0) && (column <= 7);
} // Position::isValid

int Position::getRow() const {
    return row;
} // Position::getRow

int Position::getColumn() const {
    return column;
} // Position::getColumn
