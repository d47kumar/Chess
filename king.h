#ifndef KING_H
#define KING_H
#include <iostream>;
#include <cmath>;
#include "piece.h";

class King : public Piece {
    public:
        // Constructors
        King(const std::string colour, Position pos, bool hasMoved);

        // Methods
        bool isValidMove(Position movePosition) const override;
        bool isCheck();
        bool isCheck(Position pos);
        bool isKingCheckmate();
        bool isKingStalemate();
};

#endif
