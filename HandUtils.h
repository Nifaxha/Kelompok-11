#pragma once
#include <map>
#include <vector>
#include "Hand.h"

class HandUtils {
public:
    static std::map<int, int> countRanks(const Hand& hand);
    static std::map<int, int> countSuits(const Hand& hand);
    static std::vector<int> getSortedRanks(const Hand& hand);

    static bool isFlush(const Hand& hand);
    static bool isStraight(const Hand& hand);
    static bool isRoyal(const Hand& hand);

    static bool hasNOfAKind(const Hand& hand, int n);
    static int numberOfPairs(const Hand& hand);

    static bool isPair(const Hand& hand);
    static bool isTwoPair(const Hand& hand);
    static bool isThreeOfAKind(const Hand& hand);
    static bool isFullHouse(const Hand& hand);
    static bool isFourOfAKind(const Hand& hand);
    static bool isStraightFlush(const Hand& hand);
    static bool isRoyalFlush(const Hand& hand);
    static bool isFiveOfAKind(const Hand& hand);
    static bool isFlushHouse(const Hand& hand);
    static bool isFlushFive(const Hand& hand);
};