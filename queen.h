#ifndef QUEEN_H
#define QUEEN_H
#include <memory>
#include "piece.h"
#include "board.h"

class Board;

class Queen : public Piece {
    public:
        // Constructor
        Queen(const std::string colour, Position pos, bool hasMoved);
        std::unique_ptr<Piece> clone() const override;

        // Methods
        bool isValidMove(Position movePosition, Board *board) const override;
};


#endif
