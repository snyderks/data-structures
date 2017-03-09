//
// Created by Kristian Snyder on 2/26/17.
//

#include "Disk.h"

Disk::Disk(int diskVal, int playerNum) {
    value = diskVal;
    playerNumber = playerNum;
}

int Disk::getValue() {
    return value;
}

int Disk::getPlayerNumber() {
    return playerNumber;
}

bool Disk::operator< (Disk &rhs) const {
    // less than if the value is lower or if the player numbers are different and the values are the same
    return value < rhs.getValue() || (playerNumber != rhs.getPlayerNumber() && value == rhs.getValue());
}