#include "pawn.h"
#include "piece.h"

Pawn::Pawn(const std::string colour, Position pos, bool hasMoved) : Piece{colour, pos, hasMoved} {} // Pawn::Pawn

bool Pawn::isValidMove(Position movePosition, Board *board) const {
    if (!movePosition.isValid()) { return false; }

    int row = getPosition().getRow();
    int column = getPosition().getColumn();
    int newRow = movePosition.getRow();
    int newColumn = movePosition.getColumn();

    int direction = (getColour() == "WHITE") ? -1 : 1;

    // Forward move (1 square)
    if (newColumn == column && newRow == row + direction) {
        return board->getPiece(movePosition) == nullptr;
    }
    
    // Opening move (2 squares from the starting pos)
    if (!getHasMoved() && newColumn == column && newRow == row + 2 * direction) {
        return board->getPiece(movePosition) == nullptr && 
               board->getPiece(Position(row + direction, column)) == nullptr;
    }

    // capture logic
    if (abs(newColumn - column) == 1 && newRow == row + direction) {
        Piece* target = board->getPiece(movePosition);
        return target != nullptr && target->getColour() != getColour();
    }
    // TODO: en passant logic andf promotion piece check 
    return false;
} // Pawn::isValidMove
