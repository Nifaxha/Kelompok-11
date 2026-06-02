#include <iostream>
#include "SpadeJoker.h"

ScoreContext SpadeJoker::scoreHand(const Hand& hand) {
    ScoreContext ctx = JokerDecorator::scoreHand(hand);
    int spadeCount = 0;
    for (const Card& card : hand.cards) {
        if (card.suit == 'S' || card.suit == 's') spadeCount++;
    }
    if (spadeCount > 0) {
        int bonusMult = spadeCount * 4;
        std::cout << "[JOKER] Spade Joker mendeteksi " << spadeCount << " Sekop: +" << bonusMult << " Mult!\n";
        ctx.mult += bonusMult;
    }
    return ctx;
}