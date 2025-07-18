#include "pawn.h"
#include "piece.h"

Pawn::Pawn(const std::string colour, Position pos, bool hasMoved) : Piece{colour, pos, hasMoved} {}

bool Pawn::isValidMove(Position movePosition, Board *board) const {
    if (!movePosition.isValid()) { return false; }
    int row = getPosition().getRow();
    int column = getPosition().getColumn();
    int newRow = movePosition.getRow();
    int newColumn = movePosition.getColumn();
    int direction = (getColour() == "white") ? -1 : 1;

    // Move forward one square
    if (newColumn == column && newRow == row + direction) {
        return true;
    }
    // Move forward two squares from starting position
    if (!getHasMoved() && newColumn == column && newRow == row + 2 * direction) {
        return true;
    }
    // Capture diagonally
    if (abs(newColumn - column) == 1 && newRow == row + direction) {
        return true;
    }
    return false;
}

