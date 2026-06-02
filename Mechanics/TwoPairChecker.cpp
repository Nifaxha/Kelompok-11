#include <iostream>
#include <unordered_map>
#include "TwoPairChecker.h"

bool isTwoPair(const Hand& hand) {
    std::unordered_map<int, int> rankCounts;
    for (const Card& card : hand.cards) rankCounts[card.rank]++;
    int pairs = 0;
    for (const auto& pair : rankCounts) {
        if (pair.second >= 2) pairs++;
    }
    return pairs >= 2;
}

HandRank TwoPairChecker::check(const Hand& hand) {
    if (isTwoPair(hand)) {
        std::cout << "Detected TWO PAIR\n";
        return HandRank::TWO_PAIR;
    }
    if (nextChecker) return nextChecker->check(hand);
    return HandRank::HIGH_CARD;
}