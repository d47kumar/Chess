#ifndef BOARD_H
#define BOARD_H
#include <iostream>;
#include "subject.h";
#include "piece.h";

class Board : public Subject {
    Piece* squares[8][8];
    Position whiteKingPos;
    
};

#endif
