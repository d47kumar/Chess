#include "player.h"

Player::Player(const std::string& colour) : colour{colour} {}

std::string Player::getColour() const {
    return colour;
}
