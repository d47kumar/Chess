#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H
#include "player.h"
#include <vector>
#include <random>

class ComputerPlayer : public Player {
protected:
    std::mt19937 rng;
    int difficulty;

public:
    ComputerPlayer(const std::string& colour, int difficulty);
    bool isHuman() const override;
    Move makeMove(Board* board) override;

protected:
    virtual Move selectBestMove(const std::vector<Move>& legalMoves, Board* board);
    virtual int evaluateMove(const Move& move, Board* board);
    virtual int evaluatePosition(Board* board);
};

#endif
