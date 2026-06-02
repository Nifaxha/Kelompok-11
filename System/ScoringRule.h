#pragma once
#include "Hand.h"
#include "../System/FiveOfAKindChecker.h"
#include "../System/FlushFiveChecker.h"
#include "../System/FlushHouseChecker.h"
#include "../System/FiveOfAKindChecker.h"
#include "../System/RoyalFlushChecker.h"
#include "../System/StraightFlushChecker.h"
#include "../System/FourOfAKindChecker.h"
#include "../System/FullHouseChecker.h"
#include "../System/FlushChecker.h"
#include "../System/StraightChecker.h"
#include "../System/ThreeOfAKindChecker.h"
#include "../System/TwoPairChecker.h"
#include "../System/PairChecker.h"
#include "../System/HighCardChecker.h"
#include "IScoring.h"

class ScoringRule : public IScoring {
public:
    ScoringRule();
    int scoreHand(const Hand& hand) override; // Tambahkan override
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