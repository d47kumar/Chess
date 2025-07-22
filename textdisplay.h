#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include "observer.h"
#include "board.h"
#include <iostream>

class TextDisplay : public Observer {
    Board* board;

public:
    TextDisplay();
    ~TextDisplay();

    void setBoard(Board* b);
    void notify() override;
    void printBoard() const;

private:
    char getPieceSymbol(Piece* piece) const;
    char getSquareDisplay(int row, int col) const;
};

#endif
