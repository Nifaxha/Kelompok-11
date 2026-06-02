#pragma once
#include "JokerDecorator.h"

class GreedyJoker : public JokerDecorator {
public:
    GreedyJoker(IScoring* scoring);
    ScoreContext scoreHand(const Hand& hand) override;
};