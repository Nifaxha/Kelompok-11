#pragma once
#include "../Mechanics/PokerHandChecker.h"

class StraightChecker : public PokerHandChecker{
public:
    HandRank check(const Hand& hand) override;
};