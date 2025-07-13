#include "piece.h";

std::string Piece::getColour() const {
    return colour;
} // Piece::getColour

void Piece::setColour(std::string newColour) {
    colour = newColour;
} // Piece::setColour

bool Piece::getHasMoved() const {
    return hasMoved;
} // Piece::getHasMoved

void Piece::setHasMoved(bool b) {
    hasMoved = b;
} // Piece::setHasMoved
