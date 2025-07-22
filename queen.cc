#include "queen.h"

Queen::Queen(const std::string colour, Position pos, bool hasMoved) : Piece{colour, pos, hasMoved} {} // Queen::Queen

bool Queen::isValidMove(Position movePosition, Board *board) const {
    if (!movePosition.isValid()) { return false; }
    int row = getPosition().getRow();
    int column = getPosition().getColumn();
    int newRow = movePosition.getRow();
    int newColumn = movePosition.getColumn();

    int rowDiff = abs(newRow - row);
    int columnDiff = abs(newColumn - column);

    // Not a queen move
    if (!(row == newRow || column == newColumn || rowDiff == columnDiff)) {
        return false;
    }

    // Check for blocking pieces
    int dRow = (newRow - row) == 0 ? 0 : (newRow - row) / abs(newRow - row);
    int dCol = (newColumn - column) == 0 ? 0 : (newColumn - column) / abs(newColumn - column);
    int steps = std::max(rowDiff, columnDiff);
    for (int i = 1; i < steps; ++i) {
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
} // Queen::isValidMove

std::unique_ptr<Piece> Queen::clone() const {
    return std::make_unique<Queen>(*this);
} // Queen::clone
