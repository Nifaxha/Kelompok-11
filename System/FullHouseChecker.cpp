#include <iostream>
#include <unordered_map>
#include "FullHouseChecker.h"

bool isFullHouse(const Hand& hand) {
    std::unordered_map<int, int> rankCounts;
    for (const Card& card : hand.cards) rankCounts[card.rank]++;
    bool hasThree = false;
    int pairCount = 0;
    
    for (const auto& pair : rankCounts) {
        if (pair.second >= 3) hasThree = true;
        if (pair.second >= 2) pairCount++; 
    }
    // Jika ada 3-of-a-kind, otomatis pairCount akan menjadi minimal 1. 
    // Jadi untuk full house kita butuh pairCount >= 2.
    return hasThree && (pairCount >= 2);
}

HandRank FullHouseChecker::check(const Hand& hand) {
    if (isFullHouse(hand)) {
        std::cout << "Detected FULL HOUSE\n";
        return HandRank::FULL_HOUSE;
    }
    if (nextChecker) return nextChecker->check(hand);
    return HandRank::HIGH_CARD;
}