#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "StraightFlushChecker.h"

bool isStraightFlush(const Hand& hand) {
    if (hand.cards.size() < 5) return false;
    
    // Cek Flush
    std::unordered_map<char, int> suitCounts;
    for (const Card& card : hand.cards) suitCounts[card.suit]++;
    bool isFlush = false;
    for (const auto& pair : suitCounts) if (pair.second >= 5) isFlush = true;
    
    // Cek Straight
    std::vector<int> ranks;
    for (const Card& card : hand.cards) ranks.push_back(card.rank);
    std::sort(ranks.begin(), ranks.end());
    ranks.erase(std::unique(ranks.begin(), ranks.end()), ranks.end());
    
    bool isStraight = false;
    if (ranks.size() >= 5) {
        for (size_t i = 0; i <= ranks.size() - 5; ++i) {
            if (ranks[i+4] - ranks[i] == 4) isStraight = true;
        }
        if (ranks.back() == 14 && ranks[0] == 2 && ranks[1] == 3 && ranks[2] == 4 && ranks[3] == 5) isStraight = true;
    }
    
    return isFlush && isStraight;
}

HandRank StraightFlushChecker::check(const Hand& hand) {
    if (isStraightFlush(hand)) {
        std::cout << "Detected STRAIGHT FLUSH\n";
        return HandRank::STRAIGHT_FLUSH;
    }
    if (nextChecker) return nextChecker->check(hand);
    return HandRank::HIGH_CARD;
}