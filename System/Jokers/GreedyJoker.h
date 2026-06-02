#include <iostream>
#include "GreedyJoker.h"

GreedyJoker::GreedyJoker(IScoring* scoring) : JokerDecorator(scoring) {}

ScoreContext GreedyJoker::scoreHand(const Hand& hand) {
    ScoreContext ctx = JokerDecorator::scoreHand(hand);

    // Cek apakah chips dasar tinggi (indikasi hand bagus, misal Straight ke atas)
    if (ctx.chips >= 30) {
        std::cout << "[Joker Active] Greedy Joker: Kombinasi kuat! Multiplier dikalikan x2!\n";
        ctx.mult *= 2; 
    }

    return ctx;
}   