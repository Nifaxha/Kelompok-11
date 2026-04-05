#pragma once
#include "../Logic/PokerHandChecker.h"

class FlushFiveChecker : public PokerHandChecker{
public:
    HandRank check(const Hand& hand) override;
};