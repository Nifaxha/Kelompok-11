#include <iostream>
#include <unordered_map>
#include "FourOfAKindChecker.h"

bool isFourOfAKind(const Hand& hand) {
    std::unordered_map<int, int> rankCounts;
    for (const Card& card : hand.cards) rankCounts[card.rank]++;
    for (const auto& pair : rankCounts) {
        if (pair.second >= 4) return true;
    }
    return false;
}

HandRank FourOfAKindChecker::check(const Hand& hand) {
    if (isFourOfAKind(hand)) {
        std::cout << "Detected FOUR OF A KIND\n";
        return HandRank::FOUR_OF_A_KIND;
    }
    if (nextChecker) return nextChecker->check(hand);
    return HandRank::HIGH_CARD;
}