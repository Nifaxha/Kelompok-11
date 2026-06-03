#include <iostream>
#include "HandState.h"

void HandState::drawFromDeck(Deck& deck, int maxHandSize) {
    int cardsNeeded = maxHandSize - static_cast<int>(activeCards.size()); 
    for (int i = 0; i < cardsNeeded && !deck.isEmpty(); ++i) {
        activeCards.push_back(deck.drawCard());
    }
}

Hand HandState::getHandAsStruct() const {
    Hand h;
    h.cards = activeCards;
    return h;
}

void HandState::removePlayedCards(const ChosenHand& chosen) {
    for (const Card& playedCard : chosen.selectedCards) {
        for (auto it = activeCards.begin(); it != activeCards.end(); ++it) {
            if (it->rank == playedCard.rank && it->suit == playedCard.suit) {
                activeCards.erase(it);
                break;
            }
        }
    }
}

void HandState::clearHand() {
    activeCards.clear();
}