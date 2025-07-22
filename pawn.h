#ifndef PAWN_H
#define PAWN_H
#include <memory>
#include "piece.h"
#include "board.h"

class Board;

class Pawn : public Piece {
    public:
        // Constructor
        Pawn(const std::string colour, Position pos, bool hasMoved);
        std::unique_ptr<Piece> clone() const override;

        // Methods
        bool isValidMove(Position movePosition, Board *board) const override;
};

#endif
