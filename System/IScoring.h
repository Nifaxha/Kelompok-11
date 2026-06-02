#pragma once
#include "Hand.h"

class IScoring {
public:
    virtual ~IScoring() = default;
    virtual int scoreHand(const Hand& hand) = 0;
};