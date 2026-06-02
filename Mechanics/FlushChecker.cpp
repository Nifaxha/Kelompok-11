#include <iostream>
#include <unordered_map>
#include "FlushChecker.h"

bool isFlush(const Hand& hand) {
    if (hand.cards.size() < 5) return false;
    std::unordered_map<char, int> suitCounts;
    for (const Card& card : hand.cards) suitCounts[card.suit]++;
    for (const auto& pair : suitCounts) {
        if (pair.second >= 5) return true;
    }
    return false;
}

HandRank FlushChecker::check(const Hand& hand) {
    if (isFlush(hand)) {
        std::cout << "Detected FLUSH\n";
        return HandRank::FLUSH;
    }
    if (nextChecker) return nextChecker->check(hand);
    return HandRank::HIGH_CARD;
}