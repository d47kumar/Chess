#ifndef KNIGHT_H
#define KNIGHT_H
#include <iostream>
#include <cmath>
#include "piece.h"

class Knight : public Piece {
    public:
        // Constructors
        Knight(const std::string colour, Position pos, bool hasMoved);

        // Methods
        bool isValidMove(Position movePosition) const override;
};

#endif
