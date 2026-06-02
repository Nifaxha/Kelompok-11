#include <iostream>
#include "JollyJoker.h"

ScoreContext JollyJoker::scoreHand(const Hand& hand) {
    ScoreContext ctx = JokerDecorator::scoreHand(hand);
    std::cout << "[JOKER] Jolly Joker aktif: +8 Multiplier!\n";
    ctx.mult += 8; 
    return ctx;
}