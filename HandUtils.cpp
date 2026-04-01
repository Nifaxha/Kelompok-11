#include "HandUtils.h"
#include <algorithm>

std::map<int, int> HandUtils::countRanks(const Hand& hand) {
    std::map<int, int> freq;
    for (const auto& card : hand.cards) {
        freq[(int)card.rank]++;
    }
    return freq;
}

std::map<int, int> HandUtils::countSuits(const Hand& hand) {
    std::map<int, int> freq;
    for (const auto& card : hand.cards) {
        freq[(int)card.suit]++;
    }
    return freq;
}

std::vector<int> HandUtils::getSortedRanks(const Hand& hand) {
    std::vector<int> ranks;
    for (const auto& card : hand.cards) {
        ranks.push_back((int)card.rank);
    }
    std::sort(ranks.begin(), ranks.end());
    return ranks;
}

bool HandUtils::isFlush(const Hand& hand) {
    if (hand.cards.empty()) return false;
    Suit firstSuit = hand.cards[0].suit;
    for (const auto& card : hand.cards) {
        if (card.suit != firstSuit) return false;
    }
    return true;
}

bool HandUtils::isStraight(const Hand& hand) {
    if (hand.cards.size() != 5) return false;

    std::vector<int> ranks = getSortedRanks(hand);

    std::vector<int> uniqueRanks = ranks;
    uniqueRanks.erase(std::unique(uniqueRanks.begin(), uniqueRanks.end()), uniqueRanks.end());
    if (uniqueRanks.size() != 5) return false;

    bool normalStraight = true;
    for (int i = 1; i < 5; ++i) {
        if (ranks[i] != ranks[i - 1] + 1) {
            normalStraight = false;
            break;
        }
    }
    if (normalStraight) return true;

    std::vector<int> aceLow = {2, 3, 4, 5, 14};
    return ranks == aceLow;
}

bool HandUtils::isRoyal(const Hand& hand) {
    if (hand.cards.size() != 5) return false;
    std::vector<int> ranks = getSortedRanks(hand);
    std::vector<int> royal = {10, 11, 12, 13, 14};
    return ranks == royal;
}

bool HandUtils::hasNOfAKind(const Hand& hand, int n) {
    auto freq = countRanks(hand);
    for (const auto& entry : freq) {
        if (entry.second == n) return true;
    }
    return false;
}

int HandUtils::numberOfPairs(const Hand& hand) {
    auto freq = countRanks(hand);
    int pairs = 0;
    for (const auto& entry : freq) {
        if (entry.second == 2) pairs++;
    }
    return pairs;
}

bool HandUtils::isPair(const Hand& hand) {
    return numberOfPairs(hand) == 1 && !isThreeOfAKind(hand) && !isFullHouse(hand);
}

bool HandUtils::isTwoPair(const Hand& hand) {
    return numberOfPairs(hand) == 2;
}

bool HandUtils::isThreeOfAKind(const Hand& hand) {
    auto freq = countRanks(hand);
    bool hasThree = false;
    for (const auto& entry : freq) {
        if (entry.second == 3) hasThree = true;
    }
    return hasThree && !isFullHouse(hand);
}

bool HandUtils::isFullHouse(const Hand& hand) {
    auto freq = countRanks(hand);
    bool hasThree = false;
    bool hasTwo = false;

    for (const auto& entry : freq) {
        if (entry.second == 3) hasThree = true;
        if (entry.second == 2) hasTwo = true;
    }

    return hasThree && hasTwo;
}

bool HandUtils::isFourOfAKind(const Hand& hand) {
    return hasNOfAKind(hand, 4);
}

bool HandUtils::isStraightFlush(const Hand& hand) {
    return isStraight(hand) && isFlush(hand);
}

bool HandUtils::isRoyalFlush(const Hand& hand) {
    return isStraightFlush(hand) && isRoyal(hand);
}

bool HandUtils::isFiveOfAKind(const Hand& hand) {
    return hasNOfAKind(hand, 5);
}

bool HandUtils::isFlushHouse(const Hand& hand) {
    return isFlush(hand) && isFullHouse(hand);
}

bool HandUtils::isFlushFive(const Hand& hand) {
    return isFlush(hand) && isFiveOfAKind(hand);
}