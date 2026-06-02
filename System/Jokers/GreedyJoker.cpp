#include <iostream>
#include "GreedyJoker.h"

ScoreContext GreedyJoker::scoreHand(const Hand& hand) {
    ScoreContext ctx = JokerDecorator::scoreHand(hand);
    // Jika chips dari kombinasi kartu >= 30 (Straight ke atas)
    if (ctx.chips >= 30) {
        std::cout << "[JOKER] Greedy Joker mendeteksi kombinasi kuat: Multiplier x2!\n";
        ctx.mult *= 2; 
    }
    return ctx;
}