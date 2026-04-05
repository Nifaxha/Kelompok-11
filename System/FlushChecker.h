#pragma once
#include "../Logic/PokerHandChecker.h"

class FlushChecker : public PokerHandChecker{
public:
    HandRank check(const Hand& hand) override;
};