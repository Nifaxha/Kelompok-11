#include <iostream>
#include <unordered_map>
#include "ThreeOfAKindChecker.h"

bool isThreeOfAKind(const Hand& hand) {
    std::unordered_map<int, int> rankCounts;
    for (const Card& card : hand.cards) rankCounts[card.rank]++;
    for (const auto& pair : rankCounts) {
        if (pair.second >= 3) return true;
    }
    return false;
}

HandRank ThreeOfAKindChecker::check(const Hand& hand) {
    if (isThreeOfAKind(hand)) {
        std::cout << "Detected THREE OF A KIND\n";
        return HandRank::THREE_OF_A_KIND;
    }
    if (nextChecker) return nextChecker->check(hand);
    return HandRank::HIGH_CARD;
}