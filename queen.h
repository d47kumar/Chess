#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"

class Queen : public Piece {
    public:
        Queen(const std::string colour, Position pos, bool hasMoved);
        bool isValidMove(Position movePosition) const override;
};


#endif
