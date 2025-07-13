#include "knight.h"

bool Knight::isValidMove(Position movePosition) const {
    int row = getPosition().getRow();
    int column = getPosition().getColumn();
    int newRow = movePosition.getRow();
    int newColumn = movePosition.getColumn();

    int rowDiff = abs(newRow - row);
    int columnDiff = abs(newColumn - column);

    if (rowDiff == 1) { return (columnDiff == 2); }
    if (rowDiff == 2) { return (columnDiff == 1); }

    return false;
}
