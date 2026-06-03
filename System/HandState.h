#pragma once
#include <vector>
#include "Card.h"
#include "Hand.h"
#include "Deck.h"
#include "ChosenHand.h"
#include "Subject.h"

class HandState {
private:
    std::vector<Card> activeCards;
    int maxHandSize = 8; // Batas maksimal kartu di tangan

class HandState : public Subject { // Warisi Subject di sini
public:
    Hand currentHand;
    void drawFromDeck(Deck& deck, int maxHandSize); 
    void discard(const std::vector<int>& indices);
    void removeCards(const std::vector<int>& indices);
};
}