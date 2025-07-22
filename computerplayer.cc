#include "computerplayer.h"
#include <algorithm>
#include <random>
#include <chrono>

ComputerPlayer::ComputerPlayer(const std::string& colour, int difficulty) 
    : Player{colour}, difficulty{difficulty}, rng{std::chrono::steady_clock::now().time_since_epoch().count()} {}

bool ComputerPlayer::isHuman() const {
    return false;
}

Move ComputerPlayer::makeMove(Board* board) {
    std::vector<Move> legalMoves = board->getLegalMoves(colour);

    if (legalMoves.empty()) {
        // No legal moves - this should be handled by the game controller
        return Move(Position(-1, -1), Position(-1, -1));
    }

    return selectBestMove(legalMoves, board);
}

Move ComputerPlayer::selectBestMove(const std::vector<Move>& legalMoves, Board* board) {
    // Default: random move (Level 1)
    std::uniform_int_distribution<> dist(0, legalMoves.size() - 1);
    return legalMoves[dist(rng)];
}

int ComputerPlayer::evaluateMove(const Move& move, Board* board) {
    int score = 0;

    // Check if move captures a piece
    Piece* target = board->getPiece(move.to);
    if (target && target->getColour() != colour) {
        score += 10; // Basic capture bonus
    }

    return score;
}

int ComputerPlayer::evaluatePosition(Board* board) {
    // Basic material evaluation
    int score = 0;

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            Piece* piece = board->getPiece(Position(row, col));
            if (piece) {
                int value = 0;
                // Simple piece values
                if (dynamic_cast<Pawn*>(piece)) value = 1;
                else if (dynamic_cast<Knight*>(piece) || dynamic_cast<Bishop*>(piece)) value = 3;
                else if (dynamic_cast<Rook*>(piece)) value = 5;
                else if (dynamic_cast<Queen*>(piece)) value = 9;
                else if (dynamic_cast<King*>(piece)) value = 100;

                if (piece->getColour() == colour) {
                    score += value;
                } else {
                    score -= value;
                }
            }
        }
    }

    return score;
}
