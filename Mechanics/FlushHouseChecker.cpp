#include <iostream>
#include <unordered_map>
#include "FlushHouseChecker.h"

bool isFlushHouse(const Hand& hand) {
    std::unordered_map<char, int> suitCounts;
    std::unordered_map<int, int> rankCounts;
    
    for (const Card& card : hand.cards) {
        suitCounts[card.suit]++;
        rankCounts[card.rank]++;
    }
    
    bool isFlush = false;
    for (const auto& pair : suitCounts) if (pair.second >= 5) isFlush = true;
    
    bool hasThree = false; int pairCount = 0;
    for (const auto& pair : rankCounts) {
        if (pair.second >= 3) hasThree = true;
        if (pair.second >= 2) pairCount++;
    }
    bool isFullHouse = hasThree && (pairCount >= 2);
    
    return isFlush && isFullHouse;
}

HandRank FlushHouseChecker::check(const Hand& hand) {
    if (isFlushHouse(hand)) {
        std::cout << "Detected FLUSH HOUSE\n";
        return HandRank::FLUSH_HOUSE;
    }
    if (nextChecker) return nextChecker->check(hand);
    return HandRank::HIGH_CARD;
}