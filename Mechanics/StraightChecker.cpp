#include <iostream>
#include <vector>
#include <algorithm>
#include "StraightChecker.h"

bool isStraight(const Hand& hand) {
    if (hand.cards.size() < 5) return false;
    std::vector<int> ranks;
    for (const Card& card : hand.cards) ranks.push_back(card.rank);
    
    std::sort(ranks.begin(), ranks.end());
    ranks.erase(std::unique(ranks.begin(), ranks.end()), ranks.end()); // Hapus angka duplikat
    
    if (ranks.size() < 5) return false;
    
    // Cek urutan 5 kartu berderet
    for (size_t i = 0; i <= ranks.size() - 5; ++i) {
        if (ranks[i+4] - ranks[i] == 4) return true;
    }
    
    // Cek khusus untuk Ace Low Straight (Ace bernilai 1) => A, 2, 3, 4, 5
    if (ranks.back() == 14 && ranks[0] == 2 && ranks[1] == 3 && ranks[2] == 4 && ranks[3] == 5) return true;
    
    return false;
}

HandRank StraightChecker::check(const Hand& hand) {
    if (isStraight(hand)) {
        std::cout << "Detected STRAIGHT\n";
        return HandRank::STRAIGHT;
    }
    if (nextChecker) return nextChecker->check(hand);
    return HandRank::HIGH_CARD;
}