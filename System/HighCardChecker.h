#pragma once
#include "../Mechanics/PokerHandChecker.h"

class HighCardChecker : public PokerHandChecker{
public:
    HandRank check(const Hand& hand) override;
};