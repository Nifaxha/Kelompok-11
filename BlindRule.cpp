#include <iostream>
#include "BlindRule.h"

BlindRule::BlindRule(int target) : targetScore(target) {}

bool BlindRule::checkBlind(int score) {
    std::cout << "Checking blind requirement...\n";
    std::cout << "Target score  : " << targetScore << "\n";
    std::cout << "Player score  : " << score << "\n";

    bool win = score >= targetScore;
    std::cout << "Result        : " << (win ? "WIN" : "LOSE") << "\n";

    return win;
}