#pragma once
#include "JokerDecorator.h"

class GreedyJoker : public JokerDecorator {
public:
    GreedyJoker(IScoring* scoring);
    int scoreHand(const Hand& hand) override;
};