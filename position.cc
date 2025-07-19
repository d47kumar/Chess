#include "position.h"

Position::Position(int row, int column) : row{row}, column{column} {} // Position::Position

bool Position::isValid() const {
    return (row >= 0) && (row <= 7) && (column >= 0) && (column <= 7); // Position::isValid
}

int Position::getRow() const {
    return row;
} // Position::getRow

int Position::getColumn() const {
    return column;
} // Position::getColumn

void Position::setRow(int newRow) {
    row = newRow;
} // Position::setRow

void Position::setColumn(int newColumn) {
    column = newColumn;
} // Position::setColumn

bool Position::operator<(const Position& other) const {
    if (row != other.row) {
        return row < other.row;
    }
    return column < other.column;
} // Position::operator<

bool Position::operator==(const Position& other) const {
    return row == other.row && column == other.column;
} // Position::operator==
