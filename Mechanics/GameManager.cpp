#include <iostream>
#include "GameManager.h"

void GameManager::runSession() {
    std::cout << "=== Run Started ===\n";

    // 1. Generate kartu acak
    Hand generatedHand = handGenerator.generateHand();

    // 2. Pemain memilih kartu dari tangannya
    ChosenHand chosenHand = handPlayer.playHand(generatedHand);

    // 3. Sistem mengubah ChosenHand ke Hand dasar untuk dievaluasi
    Hand handToScore = chosenHand.toHand();

    // 4. Proses skoring melewati Chain of Responsibility
    int score = scoringRule.scoreHand(handToScore);

    // 5. Cek kemenangan & Hadiah
    bool win = blindRule.checkBlind(score);
    int reward = rewardRule.earnMoney(win, score);

    std::cout << "Money gained: " << reward << "\n";
    std::cout << "=== Run Ended ===\n";
}