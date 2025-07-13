#ifndef PIECE_H
#define PIECE_H
#include <iostream>;
#include <string>;

class Piece {
    protected:
        std::string colour;
        bool hasMoved;

    public:
        // Methods
        // Count the number of legal moves
        virtual int isValidMove() = 0;

        // Getters and Setters
        // Colour
        std::string getColour() const;
        void setColour(std::string newColour);

        // hasMoved
        bool getHasMoved() const;
        void setHasMoved(bool b);
};

#endif
