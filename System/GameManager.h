#pragma once
#include <vector>
#include "HandGenerator.h"
#include "HandPlayer.h"
#include "ScoringRule.h"
#include "BlindRule.h"
#include "RewardRule.h"
#include "Jokers/JokerType.h"
#include "Jokers/Shop.h"

class GameManager {
public:
    GameManager(); // Tambahkan constructor untuk init data awal
    void runSession();

private:
    HandGenerator handGenerator;
    HandPlayer handPlayer;
    ScoringRule scoringRule;
    BlindRule blindRule;
    RewardRule rewardRule;
    Shop shop;

    // State data milik pemain yang bertahan antar-round
    int playerMoney;
    std::vector<JokerType> ownedJokers;
};