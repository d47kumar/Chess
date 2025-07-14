#include "piece.h";

Piece::Piece(const std::string colour, Position pos, bool hasMoved) : colour{colour}, pos{pos}, hasMoved{hasMoved} {};

std::string Piece::getColour() const {
    return colour;
} // Piece::getColour

Position Piece::getPosition() const {
    return pos;
} // Piece::getPosition

void Piece::setPosition(Position newPosition) {
    pos = newPosition;
} // Piece::setPosition

bool Piece::getHasMoved() const {
    return hasMoved;
} // Piece::getHasMoved

void Piece::setHasMoved(bool b) {
    hasMoved = b;
} // Piece::setHasMoved
