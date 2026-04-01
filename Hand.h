#pragma once
#include <vector>
#include "Card.h"

struct Hand {
    std::vector<Card> cards;
};

void printHand(const Hand& hand);