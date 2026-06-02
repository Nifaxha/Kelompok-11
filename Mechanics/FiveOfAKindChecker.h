#pragma once
#include "../Mechanics/PokerHandChecker.h"

class FiveOfAKindChecker : public PokerHandChecker{
public:
    HandRank check(const Hand& hand) override;
};