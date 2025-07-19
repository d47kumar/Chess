#include "graphicaldisplay.h"

GraphicalDisplay::GraphicalDisplay() {
    window = std::make_unique<Xwindow>(windowSize, windowSize);
    board = nullptr;
} // GraphicalDisplay::GraphicalDisplay

GraphicalDisplay::~GraphicalDisplay() {} // GraphicalDisplay::~GraphicalDisplay

void GraphicalDisplay::setBoard(Board* b) {
    board = b;
    drawBoard();
} // GraphicalDisplay::setBoard

void GraphicalDisplay::notify() {
    if (board) {
        drawBoard();
    }
} // GraphicalDisplay::notify

void GraphicalDisplay::drawBoard() {
    if (!window || !board) return;

    window->fillRectangle(0, 0, windowSize, windowSize, Xwindow::White);

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            int x = col * squareSize;
            int y = row * squareSize;

            int colour = ((row + col) % 2 == 0) ? Xwindow::White : Xwindow::Black;
            window->fillRectangle(x, y, squareSize, squareSize, colour);

            Piece* piece = board->getPiece(Position(row, col));
            if (piece) {
                char symbol = getPieceSymbol(piece);
                int textX = x + squareSize / 2 - 10;
                int textY = y + squareSize / 2 + 10;

                window->drawString(textX, textY, std::string(1, symbol));
            }
        }
    }
} // GraphicalDisplay::drawBoard

void GraphicalDisplay::drawPiece(char piece, int row, int col) {
    if (!window) return;

    int x = col * squareSize;
    int y = row * squareSize;

    int colour = ((row + col) % 2 == 0) ? Xwindow::White : Xwindow::Black;
    window->fillRectangle(x, y, squareSize, squareSize, colour);

    int textX = x + squareSize / 2 - 10;
    int textY = y + squareSize / 2 + 10;

    window->drawString(textX, textY, std::string(1, piece));
} // GraphicalDisplay::drawPiece

int GraphicalDisplay::getColour(int row, int col) const {
    return ((row + col) % 2 == 0) ? Xwindow::White : Xwindow::Black;
} // GraphicalDisplay::getColour

char GraphicalDisplay::getPieceSymbol(Piece* piece) const {
    if (!piece) return ' ';

    bool isWhite = (piece->getColour() == "WHITE");

    if (dynamic_cast<King*>(piece)) return isWhite ? 'K' : 'k';
    if (dynamic_cast<Queen*>(piece)) return isWhite ? 'Q' : 'q';
    if (dynamic_cast<Rook*>(piece)) return isWhite ? 'R' : 'r';
    if (dynamic_cast<Bishop*>(piece)) return isWhite ? 'B' : 'b';
    if (dynamic_cast<Knight*>(piece)) return isWhite ? 'N' : 'n';
    if (dynamic_cast<Pawn*>(piece)) return isWhite ? 'P' : 'p';

    return '?';
} // GraphicalDisplay::getPieceSymbol
