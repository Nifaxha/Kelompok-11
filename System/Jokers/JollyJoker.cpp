#include <iostream>
#include "JollyJoker.h"

JollyJoker::JollyJoker(IScoring* scoring) : JokerDecorator(scoring) {}

ScoreContext JollyJoker::scoreHand(const Hand& hand) {
    ScoreContext ctx = JokerDecorator::scoreHand(hand); // Tarik data chips & mult
    
    std::cout << "[Joker Active] Jolly Joker: Memberikan +4 Multiplier!\n";
    ctx.mult += 4; // Hanya ubah multiplier
    
    return ctx;
}