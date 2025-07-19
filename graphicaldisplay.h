#ifndef GRAPHICALDISPLAY_H
#define GRAPHICALDISPLAY_H
#include "observer.h"
#include "board.h"
#include <iostream>
#include "window.h"

class GraphicalDisplay : public Observer {
    const int windowSize = 500;
    const int squareSize = windowSize / 8;
    std::unique_ptr<Xwindow> window;
    Board* board;

public:
    GraphicalDisplay();
    ~GraphicalDisplay();

    void setBoard(Board* b);
    void notify() override;
    void drawBoard();
    void drawPiece(char piece, int row, int col);

private:
    int getColour(int row, int col) const; 
    char getPieceSymbol(Piece* piece) const;
};

#endif
