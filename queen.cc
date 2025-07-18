#include "queen.h"
#include "piece.h"

Queen::Queen(const std::string colour, Position pos, bool hasMoved) : Piece{colour, pos, hasMoved} {}

bool Queen::isValidMove(Position movePosition, Board *board) const {
    if (!movePosition.isValid()) { return false; }
    int row = getPosition().getRow();
    int column = getPosition().getColumn();
    int newRow = movePosition.getRow();
    int newColumn = movePosition.getColumn();

    // Same row or same column
    if (row == newRow || column == newColumn) {
        return true;
    }
    // Diagonal
    if (abs(newRow - row) == abs(newColumn - column)) {
        return true;
    }
    return false;
}
