#pragma once
#include "JokerDecorator.h"
#include "../IObserver.h" // Tambahkan ini

class BasicJoker : public JokerDecorator, public IObserver { // Warisi IObserver
private:
    int baseMult = 8;
    int bonusMult = 0; // Memori penyimpanan bonus observer
public:
    BasicJoker(IScoring* scoring);
    ScoreContext scoreHand(const Hand& hand) override;
    void onNotify(const std::string& eventName) override;
};