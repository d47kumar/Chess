// Move.h
#ifndef MOVE_H
#define MOVE_H

#include "position.h"

enum class PieceType { None, Queen, Rook, Bishop, Knight }; // For promotion

class Move {
public:
    Position from;
    Position to;
    bool isPromotion = false;
    bool isCastling = false;
    bool isEnPassant = false;
    PieceType promotionPiece = PieceType::None;

    Move(Position from, Position to,
         bool isPromotion = false,
         PieceType promotionPiece = PieceType::None,
         bool isCastling = false,
         bool isEnPassant = false);
};

#endif
