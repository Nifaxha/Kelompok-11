#pragma once
#include <vector>
#include "Card.h"

class Deck {
private:
    std::vector<Card> drawPile;

public:
    Deck();
    void resetAndShuffle();
    Card drawCard();
    bool isEmpty() const;
    int remainingCards() const;
    void addRandomCard();
};