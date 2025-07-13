#ifndef PIECE_H
#define PIECE_H
#include <iostream>;
#include <string>;

class Piece {
    std::string colour;
    bool pin;

    public:
        
        // Count the number of legal moves
        virtual int legal_moves() = 0;

};

#endif
