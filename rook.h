#ifndef ROOK_H
#define ROOK_H
#include <iostream>
#include <cmath>
#include "piece.h"
#include "board.h"

class Board;

class Rook : public Piece {
    public:
        // Constructors
        Rook(const std::string colour, Position pos, bool hasMoved);

        // Methods
        bool isValidMove(Position movePosition, Board *board) const override;
};

#endif
