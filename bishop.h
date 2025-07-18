#ifndef BISHOP_H
#define BISHOP_H
#include <iostream>
#include <cmath>
#include "piece.h"

class Bishop : public Piece {
    public:
        Bishop(const std::string colour, Position pos, bool hasMoved);
        bool isValidMove(Position movePosition, Board *board) const override;
};

#endif
