#ifndef BISHOP_H
#define BISHOP_H
#include <iostream>;
#include <cmath>;
#include "piece.h";

class Bishop : public Piece {
    public:
        bool isValidMove(Position movePosition) const override;
};

#endif
