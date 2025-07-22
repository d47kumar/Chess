#ifndef BISHOP_H
#define BISHOP_H
#include <iostream>
#include <cmath>
#include "piece.h"
#include "board.h"

class Board;

class Bishop : public Piece {
    public:
        // Constructor
        Bishop(const std::string colour, Position pos, bool hasMoved);

        // Methods
        bool isValidMove(Position movePosition, Board *board) const override;
};

#endif
