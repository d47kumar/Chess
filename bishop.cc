#include "bishop.h"
#include "piece.h"

Bishop::Bishop(const std::string colour, Position pos, bool hasMoved) : Piece{colour, pos, hasMoved} {} // Bishop::Bishop

bool Bishop::isValidMove(Position movePosition, Board *board) const {
    if (!movePosition.isValid()) { return false; }
    int row = getPosition().getRow();
    int column = getPosition().getColumn();
    int newRow = movePosition.getRow();
    int newColumn = movePosition.getColumn();

    // Diagonal move
    if (abs(newRow - row) == abs(newColumn - column)) {
        return true;
    }
    return false;
} // Bishop::isValidMove
