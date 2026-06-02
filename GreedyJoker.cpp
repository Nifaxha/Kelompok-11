#include <iostream>
#include "GreedyJoker.h"

GreedyJoker::GreedyJoker(IScoring* scoring) : JokerDecorator(scoring) {}

int GreedyJoker::scoreHand(const Hand& hand) {
    int baseScore = JokerDecorator::scoreHand(hand);

    // Jika skor >= 25, artinya hand tersebut minimal adalah Straight atau lebih tinggi
    if (baseScore >= 25) {
        std::cout << "[Joker Active] Greedy Joker: Kombinasi kuat terdeteksi! Skor dikalikan x2!\n";
        return baseScore * 2;
    }

    return baseScore;
}