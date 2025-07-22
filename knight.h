#ifndef KNIGHT_H
#define KNIGHT_H
#include <iostream>
#include <cmath>
#include "piece.h"
#include "board.h"

class Board;

class Knight : public Piece {
    public:
        // Constructors
        Knight(const std::string colour, Position pos, bool hasMoved);

        // Methods
        bool isValidMove(Position movePosition, Board *board) const override;
};

#endif
