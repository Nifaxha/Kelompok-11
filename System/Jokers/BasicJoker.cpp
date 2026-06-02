#include <iostream>
#include "BasicJoker.h"

// Constructor
BasicJoker::BasicJoker(IScoring* scoring) : JokerDecorator(scoring) {}

ScoreContext BasicJoker::scoreHand(const Hand& hand) {
    ScoreContext ctx = JokerDecorator::scoreHand(hand);
    std::cout << "[JOKER] Basic Joker aktif: +8 Multiplier!\n";
    ctx.mult += 8;
    return ctx;
}
