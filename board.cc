#include "board.h";

Board::Board(bool setup) : whiteKingPos(0, 4), blackKingPos(7, 4), setup{setup} {
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

Piece* Board::getPiece(Position pos) const {
    return squares.at(pos).get();
} // Board::getPiece

void Board::setPiece(Position pos, std::unique_ptr<Piece> piece) {
    int row = pos.getRow();
    int col = pos.getColumn();

    squares[{row, col}] = std::move(piece);
} // Board::setPiece
