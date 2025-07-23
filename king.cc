#include "king.h"

King::King(const std::string colour, Position pos, bool hasMoved) : Piece{colour, pos, hasMoved} {} // King::King

bool King::isValidMove(Position movePosition, Board *board) const {
    if (!movePosition.isValid()) { return false; }

    int row = getPosition().getRow();
    int column = getPosition().getColumn();
    int newRow = movePosition.getRow();
    int newColumn = movePosition.getColumn();

    int rowDiff = abs(newRow - row);
    int columnDiff = abs(newColumn - column);

    // king moves only one square
    if (rowDiff <= 1 && columnDiff <= 1 && (rowDiff != 0 || columnDiff != 0)) {
        Piece* destPiece = board->getPiece(movePosition);
        if (destPiece && destPiece->getColour() == getColour()) {
            return false; 
        }
        return true;
    }
    // checks for castling conditions
    if (rowDiff == 0 && columnDiff == 2 && !getHasMoved()) {
        Position rookPos = (newColumn > column) ? Position(row, 7) : Position(row, 0);
        return board->canCastle(getPosition(), rookPos);
    }

    return false;

    return false;
} // King::isValidMove

std::unique_ptr<Piece> King::clone() const {
    return std::make_unique<King>(*this);
} // King::clone
