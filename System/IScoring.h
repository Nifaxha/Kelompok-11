#pragma once
#include "Hand.h"
#include "ScoreContext.h" // Tambahkan ini

class IScoring {
public:
    virtual ~IScoring() = default;
    virtual ScoreContext scoreHand(const Hand& hand) = 0; // Ubah int jadi ScoreContext
};