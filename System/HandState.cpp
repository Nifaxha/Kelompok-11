#include <iostream>
#include "HandState.h"

void HandState::drawFromDeck(Deck& deck, int maxHandSize) {
    int cardsNeeded = maxHandSize - static_cast<int>(activeCards.size()); // fill up to max hand size
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
    std::cout << "[AKSI] " << indices.size() << " kartu berhasil di-discard.\n";
    notifyObservers("DISCARD"); // <--- Penyiaran terjadi di sini!
}
}