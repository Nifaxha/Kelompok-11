#pragma once
#include "../System/PokerHandChecker.h"

class PairChecker : public PokerHandChecker{
public:
    HandRank check(const Hand& hand) override;
};