#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H

#include "observer.h"
#include "board.h"
#include <iostream>

class TextDisplay : public Observer {
    Board* board; // pointer to the game board

public:
    TextDisplay(Board* b);
    void notify() override;
    void display() const;
};

#endif
