// Move.h
#ifndef MOVE_H
#define MOVE_H

#include "position.h"

class Move {
public:
    Position from;
    Position to;
    bool isPromotion = false;
    bool isCastling = false;
    bool isEnPassant = false;
    std::string promotionPiece = "";

    Move(Position from, Position to,
         bool isPromotion = false,
         std::string promotionPiece = "",
         bool isCastling = false,
         bool isEnPassant = false);
};

#endif
