#include "board.h";

Board::Board() : whiteKingPos(0, 4), blackKingPos(7, 4) {
    squares.clear();

    squares[Position(0, 0)] = std::make_unique<Rook>("BLACK", Position(0, 0), false);
    squares[Position(0, 1)] = std::make_unique<Knight>("BLACK", Position(0, 1), false);
    squares[Position(0, 2)] = std::make_unique<Bishop>("BLACK", Position(0, 2), false);
    squares[Position(0, 3)] = std::make_unique<Queen>("BLACK", Position(0, 3), false);
    squares[Position(0, 4)] = std::make_unique<King>("BLACK", Position(0, 4), false);
    squares[Position(0, 5)] = std::make_unique<Bishop>("BLACK", Position(0, 5), false);
    squares[Position(0, 6)] = std::make_unique<Knight>("BLACK", Position(0, 6), false);
    squares[Position(0, 7)] = std::make_unique<Rook>("BLACK", Position(0, 7), false);
    for (int j = 0; j < 8; ++j) {
        squares[Position(1, j)] = std::make_unique<Pawn>("BLACK", Position(1, j), false);
    }

    squares[Position(7, 0)] = std::make_unique<Rook>("WHITE", Position(7, 0), false);
    squares[Position(7, 1)] = std::make_unique<Knight>("WHITE", Position(7, 1), false);
    squares[Position(7, 2)] = std::make_unique<Bishop>("WHITE", Position(7, 2), false);
    squares[Position(7, 3)] = std::make_unique<Queen>("WHITE", Position(7, 3), false);
    squares[Position(7, 4)] = std::make_unique<King>("WHITE", Position(7, 4), false);
    squares[Position(7, 5)] = std::make_unique<Bishop>("WHITE", Position(7, 5), false);
    squares[Position(7, 6)] = std::make_unique<Knight>("WHITE", Position(7, 6), false);
    squares[Position(7, 7)] = std::make_unique<Rook>("WHITE", Position(7, 7), false);
    for (int j = 0; j < 8; ++j) {
        squares[Position(6, j)] = std::make_unique<Pawn>("WHITE", Position(6, j), false);
    }
}

Board::~Board() {} // Board::~Board

bool Board::isValidMove(Move move) {
    Position posFrom = move.getFrom();
    Position posTo = move.getTo();

    Piece* p = getPiece(posFrom);

    if (!p) {
        return false;
    }

    return p->isValidMove(posTo);
} // Board::isValidMove

bool Board::isInCheck(std::string colour) {
    Piece* w = getPiece(whiteKingPos);
    Piece* b = getPiece(blackKingPos);
    bool check = false;
    if (colour == "WHITE") {
        if (King* wk = dynamic_cast<King*>(w)) {
            check = wk->isCheck();
        }
    } else if (colour == "BLACK") {
        if (King* bk = dynamic_cast<King*>(b)) {
            check = bk->isCheck();
        }
    }
    return check;
} // Board::isInCheck

bool Board::isCheckmate(std::string colour) {
    
} // Board::isCheckmate

bool Board::isStalemate(std::string colour) {
    
} // Board::isStalemate

Piece* Board::getPiece(Position pos) const {
    return squares.at(pos).get();
} // Board::getPiece

void Board::setPiece(Position pos, std::unique_ptr<Piece> piece) {
    int row = pos.getRow();
    int col = pos.getColumn();

    squares[{row, col}] = std::move(piece);
} // Board::setPiece

