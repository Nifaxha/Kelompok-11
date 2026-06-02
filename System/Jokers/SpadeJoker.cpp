#include <iostream>
#include "SpadeJoker.h"
#include "JokerDecorator.h"
#include "../IScoring.h"

SpadeJoker::SpadeJoker(IScoring* scoring) : JokerDecorator(scoring) {}

int SpadeJoker::scoreHand(const Hand& hand) {
    int baseScore = JokerDecorator::scoreHand(hand);
    int spadeCount = 0;

    // Iterasi untuk mengecek kembang setiap kartu yang dimainkan
    for (const Card& card : hand.cards) {
        if (card.suit == 'S' || card.suit == 's') {
            spadeCount++;
        }
    }

    if (spadeCount > 0) {
        int bonus = spadeCount * 5;
        std::cout << "[Joker Active] Spade Joker: Mendeteksi " << spadeCount << " kartu Sekop. Bonus +" << bonus << "\n";
        return baseScore + bonus;
    }

    return baseScore;
}