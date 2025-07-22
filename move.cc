// Move.cc
#include "move.h"

Move::Move(Position from, Position to, bool isPromotion, std::string promotionPiece, bool isCastling, bool isEnPassant)
    : from{from}, to{to},
      isPromotion{isPromotion},
      promotionPiece{promotionPiece},
      isCastling{isCastling},
      isEnPassant{isEnPassant} {}

// Getters
Position Move::getFrom() const {
    return from;
}

Position Move::getTo() const {
    return to;
}

bool Move::getIsPromotion() const {
    return isPromotion;
}

std::string Move::getPromotionPiece() const {
    return promotionPiece;
}

bool Move::getIsCastling() const {
    return isCastling;
}

bool Move::getIsEnPassant() const {
    return isEnPassant;
}

// Setters
void Move::setFrom(Position from) {
    this->from = from;
}

void Move::setTo(Position to) {
    this->to = to;
}

void Move::setIsPromotion(bool isPromotion) {
    this->isPromotion = isPromotion;
}

void Move::setPromotionPiece(std::string promotionPiece) {
    this->promotionPiece = promotionPiece;
}

void Move::setIsCastling(bool isCastling) {
    this->isCastling = isCastling;
}

void Move::setIsEnPassant(bool isEnPassant) {
    this->isEnPassant = isEnPassant;
}

