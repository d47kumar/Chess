#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include "move.h"
#include "board.h"

class Player {
protected:
    std::string colour;

public:
    Player(const std::string& colour);
    virtual ~Player() = default;

    std::string getColour() const;
    virtual Move makeMove(Board* board) = 0;
    virtual bool isHuman() const = 0;
};

#endif
