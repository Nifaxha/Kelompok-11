#pragma once
#include "JokerDecorator.h"

class SpadesJoker : public JokerDecorator {
public:
    SpadesJoker(IScoring* scoring);
    int scoreHand(const Hand& hand) override;
};