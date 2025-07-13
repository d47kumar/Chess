#ifndef KNIGHT_H
#define KNIGHT_H
#include <iostream>;
#include <cmath>;
#include "piece.h";

class Knight : public Piece {
    public:
        bool isValidMove(Position movePosition) const override;
};

#endif
