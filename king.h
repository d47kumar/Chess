#ifndef KING_H
#define KING_H
#include <iostream>
#include <cmath>
#include "piece.h"
#include "board.h"

class Board;

class King : public Piece {
    public:
        // Constructors
        King(const std::string colour, Position pos, bool hasMoved);

        // Methods
        bool isValidMove(Position movePosition, Board *board) const override;
};

#endif
