#pragma once
#include <vector>
#include "Card.h"
#include "Hand.h"

class ChosenHand {
public:
    std::vector<Card> selectedCards;

    void addCard(const Card& card) {
        selectedCards.push_back(card);
    }

    // Mengubah ChosenHand kembali menjadi Hand agar bisa dibaca oleh PokerHandChecker
    Hand toHand() const {
        Hand h;
        h.cards = selectedCards;
        return h;
    }
};