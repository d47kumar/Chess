#ifndef ROOK_H
#define ROOK_H
#include <iostream>;
#include <cmath>;
#include "piece.h";

class Rook : public Piece {
    public:
        // Constructors
        Rook(const std::string colour, Position pos, bool hasMoved);

        // Methods
        bool isValidMove(Position movePosition) const override;
};

#endif
