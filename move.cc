// Move.cc
#include "move.h"

Move::Move(Position from, Position to, bool isPromotion, PieceType promotionPiece, bool isCastling, bool isEnPassant)
    : from{from}, to{to},
      isPromotion{isPromotion},
      promotionPiece{promotionPiece},
      isCastling{isCastling},
      isEnPassant{isEnPassant} {}

