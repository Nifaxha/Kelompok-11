#pragma once
#include "Hand.h"
#include "HandRank.h"

class PokerHandChecker {
protected:
    PokerHandChecker* nextChecker = nullptr;

public:
    virtual ~PokerHandChecker() = default;
    void setNext(PokerHandChecker* next);
    virtual HandRank check(const Hand& hand) = 0;
};