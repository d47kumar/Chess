#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H
#include "player.h"
#include <iostream>

class HumanPlayer : public Player {
public:
    HumanPlayer(const std::string& colour);
    Move makeMove(Board* board) override;
    bool isHuman() const override;

private:
    Position parsePosition(const std::string& pos) const;
};

#endif
