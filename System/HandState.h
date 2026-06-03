#pragma once
#include <vector>
#include "Card.h"
#include "Hand.h"
#include "Deck.h"
#include "ChosenHand.h"

class HandState {
private:
    std::vector<Card> activeCards;
    int maxHandSize = 8; // Batas maksimal kartu di tangan

public:
    void drawFromDeck(Deck& deck, int maxHandSize);
    Hand getHandAsStruct() const; 
    void removePlayedCards(const ChosenHand& chosen);
    void clearHand();
};