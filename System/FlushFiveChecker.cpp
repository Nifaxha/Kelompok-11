#include <iostream>
#include <unordered_map>
#include "FlushFiveChecker.h"

bool isFlushFive(const Hand& hand) {
    std::unordered_map<char, int> suitCounts;
    std::unordered_map<int, int> rankCounts;
    
    for (const Card& card : hand.cards) {
        suitCounts[card.suit]++;
        rankCounts[card.rank]++;
    }
    
    bool isFlush = false;
    for (const auto& pair : suitCounts) if (pair.second >= 5) isFlush = true;
    
    bool isFive = false;
    for (const auto& pair : rankCounts) if (pair.second >= 5) isFive = true;
    
    return isFlush && isFive;
}

HandRank FlushFiveChecker::check(const Hand& hand) {
    if (isFlushFive(hand)) {
        std::cout << "Detected FLUSH FIVE\n";
        return HandRank::FLUSH_FIVE;
    }
    if (nextChecker) return nextChecker->check(hand);
    return HandRank::HIGH_CARD;
}