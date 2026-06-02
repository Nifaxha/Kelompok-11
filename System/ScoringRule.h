#pragma once
#include "Hand.h"
#include "../Mechanics/FiveOfAKindChecker.h"
#include "../Mechanics/FlushFiveChecker.h"
#include "../Mechanics/FlushHouseChecker.h"
#include "../Mechanics/FiveOfAKindChecker.h"
#include "../Mechanics/RoyalFlushChecker.h"
#include "../Mechanics/StraightFlushChecker.h"
#include "../Mechanics/FourOfAKindChecker.h"
#include "../Mechanics/FullHouseChecker.h"
#include "../Mechanics/FlushChecker.h"
#include "../Mechanics/StraightChecker.h"
#include "../Mechanics/ThreeOfAKindChecker.h"
#include "../Mechanics/TwoPairChecker.h"
#include "../Mechanics/PairChecker.h"
#include "../Mechanics/HighCardChecker.h"
#include "IScoring.h"
#include "IScoring.h"
#include "PokerHandChecker.h"

class ScoringRule : public IScoring {
public:
    ScoringRule();
    ScoreContext scoreHand(const Hand& hand) override; // Ubah int jadi ScoreContext

private:
    FlushFiveChecker flushFiveChecker;
    FlushHouseChecker flushHouseChecker;
    FiveOfAKindChecker fiveOfAKindChecker;
    RoyalFlushChecker royalFlushChecker;
    StraightFlushChecker straightFlushChecker;
    FourOfAKindChecker fourOfAKindChecker;
    FullHouseChecker fullHouseChecker;
    FlushChecker flushChecker;
    StraightChecker straightChecker;
    ThreeOfAKindChecker threeOfAKindChecker;
    TwoPairChecker twoPairChecker;
    PairChecker pairChecker;
    HighCardChecker highCardChecker;

    int convertRankToScore(HandRank rank);
};