#include <iostream>
#include "HandState.h"

void HandState::drawFromDeck(Deck& deck) {
    int cardsNeeded = maxHandSize - activeCards.size();
    int cardsDrawn = 0;

    while (cardsNeeded > 0 && !deck.isEmpty()) {
        activeCards.push_back(deck.drawCard());
        cardsNeeded--;
        cardsDrawn++;
    }
    
    if (cardsDrawn > 0) {
        std::cout << "[SISTEM] Menarik " << cardsDrawn << " kartu. Sisa Deck: " << deck.remainingCards() << "\n";
    }
}

Hand HandState::getHandAsStruct() const {
    Hand h;
    h.cards = activeCards;
    return h;
}

void HandState::removePlayedCards(const ChosenHand& chosen) {
    // Menghapus kartu yang baru saja dimainkan (atau di-discard) agar tidak ada di tangan lagi
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