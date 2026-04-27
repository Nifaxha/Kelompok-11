#pragma once
#include "../Mechanics/PokerHandChecker.h"

class FullHouseChecker : public PokerHandChecker{
public:
    HandRank check(const Hand& hand) override;
};