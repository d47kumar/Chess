#ifndef BOARD_H
#define BOARD_H
#include <iostream>;
#include <memory>;
#include "subject.h";
#include "piece.h";
#include "move.h";
#include "king.h";
#include "queen.h";
#include "bishop.h";
#include "knight.h";
#include "rook.h";
#include "pawn.h";
#include "position.h";

class Board : public Subject {
    std::unique_ptr<Piece> squares[8][8];
    Position whiteKingPos;
    Position blackKingPos;

    public:

        // Constructor
        Board();

        // Destructor
        ~Board();

        // Methods
        bool isValidMove(Move move);
        bool isInCheck(std::string colour);
        bool isCheckmate(std::string colour);
        bool isStalemate(std::string colour);

        // Getters and Setters
        std::string getPiece(Position pos);
        void setPiece(Position pos, std::unique_ptr<Piece> piece);

        // Observer Pattern Methods
};

#endif
