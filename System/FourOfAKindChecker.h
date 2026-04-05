#pragma once
#include "../Logic/PokerHandChecker.h"

class FourOfAKindChecker : public PokerHandChecker{
public:
    HandRank check(const Hand& hand) override;
};