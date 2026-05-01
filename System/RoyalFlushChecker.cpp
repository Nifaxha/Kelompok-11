#include <iostream>
#include <unordered_map>
#include "RoyalFlushChecker.h"

bool isRoyalFlush(const Hand& hand) {
    if (hand.cards.size() < 5) return false;
    std::unordered_map<char, int> suitCounts;
    std::unordered_map<int, int> rankCounts;
    
    for (const Card& card : hand.cards) {
        suitCounts[card.suit]++;
        rankCounts[card.rank]++;
    }
    
    bool isFlush = false;
    for (const auto& pair : suitCounts) if (pair.second >= 5) isFlush = true;
    
    bool isRoyal = rankCounts[10] && rankCounts[11] && rankCounts[12] && rankCounts[13] && rankCounts[14];
    
    return isFlush && isRoyal;
}

HandRank RoyalFlushChecker::check(const Hand& hand) {
    if (isRoyalFlush(hand)) {
        std::cout << "Detected ROYAL FLUSH\n";
        return HandRank::ROYAL_FLUSH;
    }
    if (nextChecker) return nextChecker->check(hand);
    return HandRank::HIGH_CARD;
}