#pragma once
#include "../Mechanics/PokerHandChecker.h"

class RoyalFlushChecker : public PokerHandChecker{
public:
    HandRank check(const Hand& hand) override;
};