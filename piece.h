#ifndef PIECE_H
#define PIECE_H
#include <iostream>
#include <string>
#include <memory>
#include "position.h"

class Board;

class Piece {
    const std::string colour;
    Position pos;
    bool hasMoved;

    public:

        // Constructors
        Piece(const std::string colour, Position pos, bool hasMoved);
        virtual ~Piece() = default;

        // Methods
        // Count the number of legal moves
        virtual bool isValidMove(Position movePosition, Board *board) const = 0;
        virtual std::unique_ptr<Piece> clone() const = 0;

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
