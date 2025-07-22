#ifndef PAWN_H
#define PAWN_H
#include "piece.h"
#include "board.h"

class Board;

class Pawn : public Piece {
    public:
        Pawn(const std::string colour, Position pos, bool hasMoved);
        bool isValidMove(Position movePosition, Board *board) const override;
};

#endif
