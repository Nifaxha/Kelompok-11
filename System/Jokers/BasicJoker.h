#pragma once
#include "JokerDecorator.h"

class JollyJoker : public JokerDecorator {
public:
    JollyJoker(IScoring* scoring);
    ScoreContext scoreHand(const Hand& hand) override;
};