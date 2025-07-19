#include "humanplayer.h"
#include <iostream>
#include <sstream>

HumanPlayer::HumanPlayer(const std::string& colour) : Player{colour} {} // HumanPlayer::HumanPlayer

bool HumanPlayer::isHuman() const {
    return true;
} // HumanPlayer::isHuman()

Position HumanPlayer::parsePosition(const std::string& pos) const {
    if (pos.length() != 2) return Position(-1, -1); // Invalid

    char col = pos[0];
    char row = pos[1];

    if (col < 'a' || col > 'h' || row < '1' || row > '8') {
        return Position(-1, -1); // Invalid
    }

    return Position(8 - (row - '0'), col - 'a');
} // HumanPlayer::parsePosition

Move HumanPlayer::makeMove(Board* board) {
    std::string input;
    std::cout << colour << "'s turn. Enter move (e.g., e2 e4): ";

    while (std::getline(std::cin, input)) {
        std::istringstream iss(input);
        std::string from_str, to_str, promotion;

        iss >> from_str >> to_str >> promotion;

        if (from_str.empty() || to_str.empty()) {
            std::cout << "Invalid input. Please try again: ";
            continue;
        }

        Position from = parsePosition(from_str);
        Position to = parsePosition(to_str);

        if (!from.isValid() || !to.isValid()) {
            std::cout << "Invalid position. Please try again: ";
            continue;
        }

        Piece* piece = board->getPiece(from);
        if (!piece || piece->getColour() != colour) {
            std::cout << "No valid piece at " << from_str << ". Please try again: ";
            continue;
        }

        bool isPromotion = !promotion.empty();
        return Move(from, to, isPromotion, promotion);
    }

    return Move(Position(-1, -1), Position(-1, -1));
} // HumanPlayer::makeMove
