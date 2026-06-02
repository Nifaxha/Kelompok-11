#include <iostream>
#include "JollyJoker.h"

// BARIS INI YANG SEBELUMNYA TERLEWAT (Constructor)
JollyJoker::JollyJoker(IScoring* scoring) : JokerDecorator(scoring) {}

ScoreContext JollyJoker::scoreHand(const Hand& hand) {
    ScoreContext ctx = JokerDecorator::scoreHand(hand);
    std::cout << "[JOKER] Jolly Joker aktif: +8 Multiplier!\n";
    ctx.mult += 8; 
    return ctx;
}