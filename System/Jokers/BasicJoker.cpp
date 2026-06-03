#include <iostream>
#include "BasicJoker.h"

BasicJoker::BasicJoker(IScoring* scoring) : JokerDecorator(scoring) {}

ScoreContext BasicJoker::scoreHand(const Hand& hand) {
    ScoreContext ctx = JokerDecorator::scoreHand(hand);
    int totalMult = baseMult + bonusMult;
    
    std::cout << "[JOKER] Basic Joker aktif: +" << totalMult << " Multiplier!\n";
    ctx.mult += totalMult;
    return ctx;
}

void BasicJoker::onNotify(const std::string& eventName) {
    if (eventName == "DISCARD") {
        bonusMult += 2; // Setiap discard naik +2 Mult
        std::cout << "[OBSERVER] Basic Joker melihatmu membuang kartu! (Mult naik jadi: +" << (baseMult + bonusMult) << ")\n";
    }
}