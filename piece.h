#ifndef PIECE_H
#define PIECE_H
#include <iostream>
#include <string>
#include "position.h"

class Piece {
    const std::string colour;
    Position pos;
    bool hasMoved;

    public:

        // Constructors
        Piece(const std::string colour, Position pos, bool hasMoved);

        // Methods
        // Count the number of legal moves
        virtual bool isValidMove(Position movePosition) const = 0;

        // Getters and Setters
        // Colour
        std::string getColour() const;

        // Position
        Position getPosition() const;
        void setPosition(Position newPosition);

        // hasMoved
        bool getHasMoved() const;
        void setHasMoved(bool b);
};

#endif
