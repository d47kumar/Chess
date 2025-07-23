#include "pawn.h"

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

        // Normal capture
        if (target != nullptr && target->getColour() != getColour()) {
            return true;
        }

        // EN PASSAAAAANTTT
        Move lastMove = board->getLastMove();  // You already store this
        if (board->canEnPassant(getPosition(), movePosition, lastMove)) {
            return true;
        }
    } 
    return false;
} // Pawn::isValidMove

std::unique_ptr<Piece> Pawn::clone() const {
    return std::make_unique<Pawn>(*this);
} // Pawn::clone
