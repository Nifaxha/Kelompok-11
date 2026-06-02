#pragma once
#include "IScoring.h"

class JokerDecorator : public IScoring {
protected:
    IScoring* wrappedScoring; // Menampung komponen yang didekorasi

public:
    JokerDecorator(IScoring* scoring) : wrappedScoring(scoring) {}
    
    virtual ~JokerDecorator() {
        delete wrappedScoring; // Membersihkan memory leak rantai decorator
    }

    // Secara default, teruskan panggilan ke komponen di dalamnya
    int scoreHand(const Hand& hand) override {
        if (wrappedScoring) {
            return wrappedScoring->scoreHand(hand);
        }
        return 0;
    }
};