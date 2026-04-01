#include <iostream>
#include "RewardRule.h"

int RewardRule::earnMoney(bool win, int score) {
    std::cout << "Calculating reward...\n";
    if (!win) return 0;
    return score / 10;
}