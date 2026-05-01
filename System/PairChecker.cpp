#include <iostream>
#include <unordered_map>
#include "PairChecker.h"

bool isPair(const Hand& hand) {
    std::unordered_map<int, int> rankCounts;
    for (const Card& card : hand.cards) rankCounts[card.rank]++;
    for (const auto& pair : rankCounts) {
        if (pair.second >= 2) return true;
    }
    return false;
}

HandRank PairChecker::check(const Hand& hand) {
    if (isPair(hand)) {
        std::cout << "Detected PAIR\n";
        return HandRank::PAIR;
    }
    if (nextChecker) return nextChecker->check(hand);
    return HandRank::HIGH_CARD;
}