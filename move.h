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

    // Getters
    Position getFrom() const;
    Position getTo() const;
    bool getIsPromotion() const;
    std::string getPromotionPiece() const;
    bool getIsCastling() const;
    bool getIsEnPassant() const;

    // Setters
    void setFrom(Position from);
    void setTo(Position to);
    void setIsPromotion(bool isPromotion);
    void setPromotionPiece(std::string promotionPiece);
    void setIsCastling(bool isCastling);
    void setIsEnPassant(bool isEnPassant);
};

#endif
