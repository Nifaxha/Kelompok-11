#pragma once
#include "../Mechanics/PokerHandChecker.h"

class FlushHouseChecker : public PokerHandChecker{
public:
    HandRank check(const Hand& hand) override;
};