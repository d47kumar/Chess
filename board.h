#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <memory>
#include <map>
#include "subject.h"
#include "piece.h"
#include "move.h"
#include "king.h"
#include "queen.h"
#include "bishop.h"
#include "knight.h"
#include "rook.h"
#include "pawn.h"
#include "position.h"

class Board : public Subject {
    std::map<Position, std::unique_ptr<Piece>> squares;
    Position whiteKingPos;
    Position blackKingPos;
    bool setup;

    public:

        // Constructor
        Board(bool setup);

        // Destructor
        ~Board();

        // Getters and Setters
        Piece* getPiece(Position pos) const;
        void setPiece(Position pos, std::unique_ptr<Piece> piece);

        // Observer Pattern Methods
};

#endif
