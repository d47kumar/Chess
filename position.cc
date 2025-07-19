#include "position.h"

Position::Position(int row, int column) : row{row}, column{column} {}

bool Position::isValid() const {
    return (row >= 0) && (row <= 7) && (column >= 0) && (column <= 7);
}

int Position::getRow() const {
    return row;
}

int Position::getColumn() const {
    return column;
}

void Position::setRow(int newRow) {
    row = newRow;
}

void Position::setColumn(int newColumn) {
    column = newColumn;
}

bool Position::operator<(const Position& other) const {
    if (row != other.row) {
        return row < other.row;
    }
    return column < other.column;
}

bool Position::operator==(const Position& other) const {
    return row == other.row && column == other.column;
}
