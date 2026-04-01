#include <iostream>
#include "GameManager.h"
#include "Hand.h"

GameManager::GameManager() : blindRule(50) {}

void GameManager::runSession() {
    std::cout << "=== Run Started ===\n";

    Hand hand = handGenerator.generateHand();
    printHand(hand);

    handPlayer.playHand();

    int score = scoringRule.scoreHand(hand);
    bool win = blindRule.checkBlind(score);
    int reward = rewardRule.earnMoney(win, score);

    std::cout << "Money gained  : " << reward << "\n";
    std::cout << "=== Run Ended ===\n";
}