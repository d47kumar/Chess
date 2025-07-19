#include "player.h"

Player::Player(const std::string& colour) : colour{colour} {} // Player::Player

std::string Player::getColour() const {
    return colour;
} // Player::getColour
