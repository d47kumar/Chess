#ifndef PAWN_H
#define PAWN_H
#include "piece.h"

class Pawn : public Piece {
    public:
        Pawn(const std::string &colour);
        int isValidMove() override;
}


#endif
