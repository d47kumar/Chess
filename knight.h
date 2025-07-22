#ifndef KNIGHT_H
#define KNIGHT_H
#include <iostream>
#include <cmath>
#include <memory>
#include "piece.h"
#include "board.h"

class Board;

class Knight : public Piece {
    public:
        // Constructors
        Knight(const std::string colour, Position pos, bool hasMoved);
        std::unique_ptr<Piece> clone() const override;

        // Methods
        bool isValidMove(Position movePosition, Board *board) const override;
};

#endif
