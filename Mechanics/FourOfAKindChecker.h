#pragma once
#include "../Mechanics/PokerHandChecker.h"

class FourOfAKindChecker : public PokerHandChecker{
public:
    HandRank check(const Hand& hand) override;
};