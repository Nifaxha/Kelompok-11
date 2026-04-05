#pragma once
#include "../Logic/PokerHandChecker.h"

class HighCardChecker : public PokerHandChecker{
public:
    HandRank check(const Hand& hand) override;
};