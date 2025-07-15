#include "board.h";

Board::Board() : whiteKingPos(0, 4), blackKingPos(7, 4) {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            squares[i][j] = nullptr;
        }
    }

    squares[0][0] = std::make_unique<Rook>("BLACK", Position(0, 0), false);
    squares[0][1] = std::make_unique<Knight>("BLACK", Position(0, 1), false);
    squares[0][2] = std::make_unique<Bishop>("BLACK", Position(0, 2), false);
    squares[0][3] = std::make_unique<Queen>("BLACK", Position(0, 3), false);
    squares[0][4] = std::make_unique<King>("BLACK", Position(0, 4), false);
    squares[0][5] = std::make_unique<Bishop>("BLACK", Position(0, 5), false);
    squares[0][6] = std::make_unique<Knight>("BLACK", Position(0, 6), false);
    squares[0][7] = std::make_unique<Rook>("BLACK", Position(0, 7), false);
    for (int j = 0; j < 8; ++j) {
        squares[1][j] = std::make_unique<Pawn>("BLACK", Position(1, j), false);
    }

    squares[7][0] = std::make_unique<Rook>("WHITE", Position(7, 0), false);
    squares[7][1] = std::make_unique<Knight>("WHITE", Position(7, 1), false);
    squares[7][2] = std::make_unique<Bishop>("WHITE", Position(7, 2), false);
    squares[7][3] = std::make_unique<Queen>("WHITE", Position(7, 3), false);
    squares[7][4] = std::make_unique<King>("WHITE", Position(7, 4), false);
    squares[7][5] = std::make_unique<Bishop>("WHITE", Position(7, 5), false);
    squares[7][6] = std::make_unique<Knight>("WHITE", Position(7, 6), false);
    squares[7][7] = std::make_unique<Rook>("WHITE", Position(7, 7), false);
    for (int j = 0; j < 8; ++j) {
        squares[6][j] = std::make_unique<Pawn>("WHITE", Position(6, j), false);
    }
}

Board::~Board() {} // Board::~Board

bool Board::isValidMove(Move move) {} // Board::isValidMove

bool Board::isInCheck(std::string colour) {} // Board::isInCheck

bool Board::isCheckmate(std::string colour) {} // Board::isCheckmate

bool Board::isStalemate(std::string colour) {} // Board::isStalemate

std::string Board::getPiece(Position pos) {} // Board::getPiece

void Board::setPiece(Position pos, std::unique_ptr<Piece> piece) {} // Board::setPiece

