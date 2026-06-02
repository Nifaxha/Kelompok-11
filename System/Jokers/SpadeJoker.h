#pragma once
#include "JokerDecorator.h"

class SpadeJoker : public JokerDecorator {
public:
    SpadeJoker(IScoring* scoring);
    int scoreHand(const Hand& hand) override;
};