#pragma once
#include "JokerDecorator.h"

class BasicJoker : public JokerDecorator {
public:
    BasicJoker(IScoring* scoring);
    ScoreContext scoreHand(const Hand& hand) override;
};