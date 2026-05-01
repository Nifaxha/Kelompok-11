#include <iostream>
#include "HandPlayer.h"

ChosenHand HandPlayer::playHand(const Hand& hand) {
    std::cout << "Player selects cards to play...\n";
    ChosenHand chosen;

    // Simulasi Otomatis: Pemain mengambil maksimal 5 kartu pertama dari tangannya
    int cardsToPlay = std::min(5, (int)hand.cards.size());
    for (int i = 0; i < cardsToPlay; ++i) {
        chosen.addCard(hand.cards[i]);
        std::cout << "Selected Card -> Rank: " << hand.cards[i].rank << ", Suit: " << hand.cards[i].suit << "\n";
    }

    return chosen;
}