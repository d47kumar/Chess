#include "rook.h"
#include "piece.h"

Rook::Rook(const std::string colour, Position pos, bool hasMoved) : Piece{colour, pos, hasMoved} {}; // Rook::Rook

bool Rook::isValidMove(Position movePosition, Board *board) const {
    if (!movePosition.isValid()) { return false; }
    int row = getPosition().getRow();
    int column = getPosition().getColumn();
    int newRow = movePosition.getRow();
    int newColumn = movePosition.getColumn();

    int rowDiff = abs(newRow - row);
    int columnDiff = abs(newColumn - column);

    if (rowDiff > 0) { return (columnDiff == 0); }
    if (columnDiff > 0) { return (rowDiff == 0); }

    return false;

} // Rook::isValidMove