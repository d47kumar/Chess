#include "textdisplay.h"
#include "piece.h"
#include "pawn.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"
#include <cctype>
#include <iostream>

TextDisplay::TextDisplay(Board* b) : board(b) {}

TextDisplay::notify() {
    display();
}

void TextDisplay::showMessage(const std::string& message) const {
    std::cout << message << std::endl;
}

void TextDisplay::display() const {
    std::cout << std::endl;
    for (int row = 0; row < 8; ++row) {
        std::cout << (8 - row) << " ";
        for (int col = 0; col < 8; ++col) {
            Piece* p = board->getPiece(Position(row, col));
            if (p) {
                char symbol = '?';
                if (dynamic_cast<Pawn*>(p)) symbol = 'P';
                else if (dynamic_cast<Rook*>(p)) symbol = 'R';
                else if (dynamic_cast<Knight*>(p)) symbol = 'N';
                else if (dynamic_cast<Bishop*>(p)) symbol = 'B';
                else if (dynamic_cast<Queen*>(p)) symbol = 'Q';
                else if (dynamic_cast<King*>(p)) symbol = 'K';
                if (p->getColour() == "black" || p->getColour() == "BLACK") symbol = std::tolower(symbol);
                std::cout << symbol;
            } else {
                std::cout << ((row + col) % 2 == 0 ? ' ' : '_');
            }
        }
        std::cout << std::endl;
    }
    std::cout << "  abcdefgh\n" << std::endl;
}
