#ifndef BOARD_H 
#define BOARD_H 
#include <iostream> 
#include <memory> 
#include <map> 
#include <vector>
#include "piece.h"
#include "king.h"
#include "queen.h"
#include "rook.h"
#include "bishop.h"
#include "knight.h"
#include "pawn.h"
#include "subject.h"
#include "move.h" 
#include "position.h" 

// Forward declarations for all piece types
class Piece;
class King;
class Queen;
class Bishop;
class Knight;
class Rook;
class Pawn;

class Board : public Subject { 
    std::map<Position, std::unique_ptr<Piece>> squares; 
    Position whiteKingPos; 
    Position blackKingPos; 
    bool setup;
    Move lastMove;

    // Helper methods
    bool wouldBeInCheck(const std::string& colour, Move testMove) const;
    
    public: 
        // Constructor 
        Board(bool setup); 
        
        // Destructor 
        ~Board(); 
        
        // Copy constructor and assignment
        Board(const Board& other); // Copy constructor
        Board& operator=(const Board& other); // Copy assignment
        
        // Existing methods
        Move getLastMove() const;
        Piece* getPiece(Position pos) const; 
        void setPiece(Position pos, std::unique_ptr<Piece> piece); 
        void removePiece(Position pos);
        std::unique_ptr<Piece> createPiece(char pieceSymbol, Position pos, bool hasMoved) const;

        // Game logic methods
        bool isValidMove(Position from, Position to, const std::string& colour) const;
        bool isPathClear(Position from, Position to) const;
        bool isSquareUnderAttack(Position pos, const std::string& attackingColour) const;
        bool isInCheck(const std::string& colour) const;
        bool isCheckmate(const std::string& colour) const;
        bool isStalemate(const std::string& colour) const;
        std::vector<Move> getLegalMoves(const std::string& colour) const;
        
        // Special moves
        bool canCastle(Position kingPos, Position rookPos) const;
        bool canEnPassant(Position from, Position to, Move lastMove) const;
        
        // Move execution
        bool makeMove(Move move);
        
        // Board state
        void clearBoard();
        void setupStandardPosition();
        bool isValidSetup() const;
        
        // King position tracking
        Position getKingPosition(const std::string& colour) const;
        void updateKingPosition(const std::string& colour, Position newPos);
        
        // Display methods
        friend std::ostream& operator<<(std::ostream& out, const Board& board);
    
};

#endif
