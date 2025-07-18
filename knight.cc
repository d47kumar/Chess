#include "knight.h"

Knight::Knight(const std::string colour, Position pos, bool hasMoved) : Piece{colour, pos, hasMoved} {}; // Knight::Knight

bool Knight::isValidMove(Position movePosition, Board *board) const {
    if (!movePosition.isValid()) { return false; }
    int row = getPosition().getRow();
    int column = getPosition().getColumn();
    int newRow = movePosition.getRow();
    int newColumn = movePosition.getColumn();

    int rowDiff = abs(newRow - row);
    int columnDiff = abs(newColumn - column);

    if (rowDiff == 1) { return (columnDiff == 2); }
    if (rowDiff == 2) { return (columnDiff == 1); }

    return false;
} // Knight::isValidMove
