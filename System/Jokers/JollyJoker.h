#pragma once
#include "JokerDecorator.h"

class JollyJoker : public JokerDecorator {
public:
    JollyJoker(IScoring* scoring);
    int scoreHand(const Hand& hand) override;
};