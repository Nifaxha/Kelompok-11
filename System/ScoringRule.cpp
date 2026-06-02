#include <iostream>
#include "ScoringRule.h"

ScoringRule::ScoringRule(){
    flushFiveChecker.setNext(&flushHouseChecker);
    flushHouseChecker.setNext(&fiveOfAKindChecker);
    fiveOfAKindChecker.setNext(&royalFlushChecker);
    royalFlushChecker.setNext(&straightFlushChecker);
    straightFlushChecker.setNext(&fourOfAKindChecker);
    fourOfAKindChecker.setNext(&fullHouseChecker);
    fullHouseChecker.setNext(&flushChecker);
    flushChecker.setNext(&straightChecker);
    straightChecker.setNext(&threeOfAKindChecker);
    threeOfAKindChecker.setNext(&twoPairChecker);
    twoPairChecker.setNext(&pairChecker);
    pairChecker.setNext(&highCardChecker);
}

ScoreContext ScoringRule::scoreHand(const Hand& hand){
    std::cout << "Calculating hand score...\n";
    HandRank rank = flushFiveChecker.check(hand);
    return convertRankToScore(rank);
}

ScoreContext ScoringRule::convertRankToScore(HandRank rank){
    // Mengembalikan (Chips, Multiplier)
    switch (rank){
        case HandRank::FLUSH_FIVE:     return {150, 14};
        case HandRank::FLUSH_HOUSE:    return {140, 14};
        case HandRank::FIVE_OF_A_KIND: return {120, 12};
        case HandRank::ROYAL_FLUSH:    return {100, 8};
        case HandRank::STRAIGHT_FLUSH: return {100, 8};
        case HandRank::FOUR_OF_A_KIND: return {60, 7};
        case HandRank::FULL_HOUSE:     return {40, 4};
        case HandRank::FLUSH:          return {35, 4};
        case HandRank::STRAIGHT:       return {30, 4};
        case HandRank::THREE_OF_A_KIND:return {30, 3};
        case HandRank::TWO_PAIR:       return {20, 2};
        case HandRank::PAIR:           return {10, 2};
        case HandRank::HIGH_CARD:
        default:                       return {5, 1};
    }
}