#include <iostream>
#include "ScoringRule.h"

ScoringRule::ScoringRule(){
    // Rantai Chain of Responsibility
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
    
    // 1. Dapatkan skor dasar dari kombinasi Poker (Misal: Pair = 10 Chips, 2 Mult)
    HandRank rank = flushFiveChecker.check(hand);
    ScoreContext baseScore = convertRankToScore(rank);

    // 2. Hitung tambahan Chips dari setiap kartu yang dimainkan
    int cardChips = 0;
    for (const Card& card : hand.cards) {
        if (card.rank >= 2 && card.rank <= 10) {
            cardChips += card.rank; // Kartu angka 2-10 bernilai sesuai angkanya
        } else if (card.rank >= 11 && card.rank <= 13) {
            cardChips += 10; // Kartu J (11), Q (12), K (13) bernilai 10
        } else if (card.rank == 14) {
            cardChips += 11; // Kartu As (14) bernilai 11
        }
    }

    // 3. Tambahkan ke dalam total chips
    baseScore.chips += cardChips;
    std::cout << "[SISTEM] Tambahan Chips dari kartu yang dimainkan: +" << cardChips << "\n";

    return baseScore;
}

ScoreContext ScoringRule::convertRankToScore(HandRank rank){
    // Mengembalikan (Chips, Multiplier) dasar dari kombinasi
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