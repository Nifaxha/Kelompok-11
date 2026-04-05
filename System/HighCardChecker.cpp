#include <iostream>
#include "HighCardChecker.h"

HandRank HighCardChecker::check(const Hand& hand){
    (void)hand;
    std::cout << "Detected HIGH CARD\n";
    return HandRank::HIGH_CARD;
}