#pragma once
#include "JokerDecorator.h"

class SpadeJoker : public JokerDecorator {
public:
    SpadeJoker(IScoring* scoring);
    ScoreContext scoreHand(const Hand& hand) override;
};