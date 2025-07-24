#include "computerplayer.h"
#include <algorithm>

ComputerPlayer::ComputerPlayer(const std::string& colour, int difficulty, uint32_t seed)
    : Player{colour}, prng(seed), difficulty{difficulty} {}

bool ComputerPlayer::isHuman() const {
    return false;
}

Move ComputerPlayer::makeMove(Board* board) {
    std::vector<Move> legalMoves = board->getLegalMoves(colour);

    if (legalMoves.empty()) {
        return Move(Position(-1, -1), Position(-1, -1));
    }

    switch (difficulty) {
        case 1:
            return selectRandomMove(legalMoves);
        case 2:
            return selectCaptureOrCheckMove(legalMoves, board);
        case 3:
            return selectSafeCaptureOrCheckMove(legalMoves, board);
        default:
            return selectRandomMove(legalMoves);
    }
}

Move ComputerPlayer::selectRandomMove(const std::vector<Move>& legalMoves) {
    int idx = prng(legalMoves.size() - 1);
    return legalMoves[idx];
}

Move ComputerPlayer::selectCaptureOrCheckMove(const std::vector<Move>& legalMoves, Board* board) {
    std::vector<Move> captures, checks;
    for (const auto& move : legalMoves) {
        Piece* target = board->getPiece(move.to);
        if (target && target->getColour() != colour) {
            captures.push_back(move);
        } else {
            Board tempBoard = *board;
            tempBoard.makeMove(move);
            if (tempBoard.isInCheck(opponentColour())) {
                checks.push_back(move);
            }
        }
    }
    if (!captures.empty()) {
        int idx = prng(captures.size() - 1);
        return captures[idx];
    }
    if (!checks.empty()) {
        int idx = prng(checks.size() - 1);
        return checks[idx];
    }
    return selectRandomMove(legalMoves);
}

Move ComputerPlayer::selectSafeCaptureOrCheckMove(const std::vector<Move>& legalMoves, Board* board) {
    std::vector<Move> safeMoves, safeCaptures, safeChecks;
    for (const auto& move : legalMoves) {
        Board tempBoard = *board;
        tempBoard.makeMove(move);
        bool isSafe = !tempBoard.isSquareUnderAttack(move.to, opponentColour());
        Piece* target = board->getPiece(move.to);
        if (isSafe) {
            if (target && target->getColour() != colour) {
                safeCaptures.push_back(move);
            } else if (tempBoard.isInCheck(opponentColour())) {
                safeChecks.push_back(move);
            } else {
                safeMoves.push_back(move);
            }
        }
    }
    if (!safeCaptures.empty()) {
        int idx = prng(safeCaptures.size() - 1);
        return safeCaptures[idx];
    }
    if (!safeChecks.empty()) {
        int idx = prng(safeChecks.size() - 1);
        return safeChecks[idx];
    }
    if (!safeMoves.empty()) {
        int idx = prng(safeMoves.size() - 1);
        return safeMoves[idx];
    }
    return selectCaptureOrCheckMove(legalMoves, board);
}

std::string ComputerPlayer::opponentColour() const {
    return (colour == "WHITE") ? "BLACK" : "WHITE";
}
