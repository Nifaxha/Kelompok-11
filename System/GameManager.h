#pragma once
#include <vector>
#include "Deck.h"           // Menggantikan HandGenerator.h
#include "HandState.h"      // Tambahkan ini
#include "HandPlayer.h"
#include "ScoringRule.h"
#include "BlindRule.h"
#include "RewardRule.h"
#include "Jokers/JokerType.h"
#include "Jokers/Shop.h"
#include "ScoreContext.h"

class GameManager {
public:
    GameManager();
    void runSession();

private:
    Deck deck;
    HandState handState;
    HandPlayer handPlayer;
    ScoringRule scoringRule;
    BlindRule blindRule;
    RewardRule rewardRule;
    Shop shop;

    int playerMoney;
    std::vector<JokerType> ownedJokers;
};