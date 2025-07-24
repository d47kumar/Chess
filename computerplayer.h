#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H
#include "player.h"
#include "PRNG.h"
#include <vector>

class ComputerPlayer : public Player {
    PRNG prng;
    int difficulty;

public:
    ComputerPlayer(const std::string& colour, int difficulty, uint32_t seed = 362436069);
    bool isHuman() const override;
    Move makeMove(Board* board) override;

private:
    Move selectRandomMove(const std::vector<Move>& legalMoves);
    Move selectCaptureOrCheckMove(const std::vector<Move>& legalMoves, Board* board);
    Move selectSafeCaptureOrCheckMove(const std::vector<Move>& legalMoves, Board* board);
    std::string opponentColour() const;
};

#endif
