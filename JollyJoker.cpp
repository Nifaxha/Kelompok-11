#include <iostream>
#include "JollyJoker.h"

JollyJoker::JollyJoker(IScoring* scoring) : JokerDecorator(scoring) {}

int JollyJoker::scoreHand(const Hand& hand) {
    // Ambil skor dari proses sebelumnya (bisa dari ScoringRule atau Joker lain)
    int baseScore = JokerDecorator::scoreHand(hand); 
    
    std::cout << "[Joker Active] Jolly Joker: Memberikan +20 Skor!\n";
    return baseScore + 20;
}