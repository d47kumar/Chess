#ifndef PAWN_H
#define PAWN_H
#include "piece.h"

class Pawn : public Piece {
    public:
        Pawn(const std::string colour, Position pos, bool hasMoved);
        bool isValidMove(Position movePosition) const override;
};


#endif
