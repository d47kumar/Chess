#include "textdisplay.h"
#include <iostream>
#include <iomanip>

TextDisplay::TextDisplay() : board{nullptr} {}

TextDisplay::~TextDisplay() {}

void TextDisplay::setBoard(Board* b) {
    board = b;
    if (board) {
        board->attach(this);
    } else {
        std::cerr << "Error: Board is null!" << std::endl;
    }
}

void TextDisplay::notify() {
    if (board) {
        printBoard();
    }
}

void TextDisplay::printBoard() const {
    if (!board) return;

    std::cout << "Drawing Board..." << std::endl;

    // Print board from rank 8 to rank 1
    for (int row = 0; row < 8; ++row) {
        std::cout << (8 - row) << " ";

        for (int col = 0; col < 8; ++col) {
            std::cout << getSquareDisplay(row, col);
        }

        std::cout << std::endl;
    }

    // Print file letters
    std::cout << "  abcdefgh" << std::endl;
}

char TextDisplay::getSquareDisplay(int row, int col) const {
    Piece* piece = board->getPiece(Position(row, col));

    if (piece) {
        return getPieceSymbol(piece);
    } else {
        // Empty square - use space for white squares, underscore for dark squares  
        return ((row + col) % 2 == 0) ? ' ' : '_';
    }
}

char TextDisplay::getPieceSymbol(Piece* piece) const {
    if (!piece) return ' ';

    bool isWhite = (piece->getColour() == "WHITE");

    if (dynamic_cast<King*>(piece)) return isWhite ? 'K' : 'k';
    if (dynamic_cast<Queen*>(piece)) return isWhite ? 'Q' : 'q';
    if (dynamic_cast<Rook*>(piece)) return isWhite ? 'R' : 'r';
    if (dynamic_cast<Bishop*>(piece)) return isWhite ? 'B' : 'b';
    if (dynamic_cast<Knight*>(piece)) return isWhite ? 'N' : 'n';
    if (dynamic_cast<Pawn*>(piece)) return isWhite ? 'P' : 'p';

    return '?';
}
