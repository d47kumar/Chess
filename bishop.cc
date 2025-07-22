#include "bishop.h"

Bishop::Bishop(const std::string colour, Position pos, bool hasMoved) : Piece{colour, pos, hasMoved} {} // Bishop::Bishop

bool Bishop::isValidMove(Position movePosition, Board *board) const {
    if (!movePosition.isValid()) { return false; }
    int row = getPosition().getRow();
    int column = getPosition().getColumn();
    int newRow = movePosition.getRow();
    int newColumn = movePosition.getColumn();

    int rowDiff = abs(newRow - row);
    int columnDiff = abs(newColumn - column);

    // Not a bishop move or no move at all
    if (rowDiff != columnDiff || rowDiff == 0) {
        return false;
    }

    // Check for blocking pieces
    int dRow = (newRow - row) / rowDiff;
    int dCol = (newColumn - column) / columnDiff;
    for (int i = 1; i < rowDiff; ++i) {
        Position intermediate(row + i * dRow, column + i * dCol);
        if (board->getPiece(intermediate) != nullptr) {
            return false;
        }
    }

    Piece* destPiece = board->getPiece(movePosition);
    if (destPiece && destPiece->getColour() == getColour()) {
        return false;
    }
    return true;
} // Bishop::isValidMove
