#ifndef KING_H
#define KING_H
#include <iostream>
#include <cmath>
#include <memory>
#include "piece.h"
#include "board.h"

class Board;

class King : public Piece {
    public:
        // Constructors
        King(const std::string colour, Position pos, bool hasMoved);
        std::unique_ptr<Piece> clone() const override;

        // Methods
        bool isValidMove(Position movePosition, Board *board) const override;
};

#endif
