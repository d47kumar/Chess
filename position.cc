#include "position.h";

Position::Position(int row, int column, bool occupied) : row{row}, column{column} {};

bool Position::isValid() const {
    return (row >= 0) && (row <= 7) && (column >= 0) && (column <= 7);
} // Position::isValid

int Position::getRow() const {
    return row;
} // Position::getRow

int Position::getColumn() const {
    return column;
} // Position::getColumn

void Position::setRow(int newRow) {
    row = newRow;
};

void Position::setColumn(int newColumn) {
    column = newColumn;
};
