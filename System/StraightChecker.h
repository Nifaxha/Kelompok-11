#pragma once
#include "../Logic/PokerHandChecker.h"

class StraightChecker : public PokerHandChecker{
public:
    HandRank check(const Hand& hand) override;
};