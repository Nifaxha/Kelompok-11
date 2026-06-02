#include <iostream>
#include <unordered_map>
#include "FiveOfAKindChecker.h"

bool isFiveOfAKind(const Hand& hand) {
    std::unordered_map<int, int> rankCounts;
    for (const Card& card : hand.cards) rankCounts[card.rank]++;
    for (const auto& pair : rankCounts) {
        if (pair.second >= 5) return true;
    }
    return false;
}

HandRank FiveOfAKindChecker::check(const Hand& hand) {
    if (isFiveOfAKind(hand)) {
        std::cout << "Detected FIVE OF A KIND\n";
        return HandRank::FIVE_OF_A_KIND;
    }
    if (nextChecker) return nextChecker->check(hand);
    return HandRank::HIGH_CARD;
}