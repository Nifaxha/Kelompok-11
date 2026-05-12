#include <iostream>
#include "GameManager.h"

void GameManager::runSession() {
    std::cout << "=== Balatro Clone Started ===\n";

    // 1. Generate 8 kartu
    Hand generatedHand = handGenerator.generateHand();

    // 2. Player milih manual (maks 5)
    ChosenHand chosenHand = handPlayer.playHand(generatedHand);

    // 3. Konversi format
    Hand handToScore = chosenHand.toHand();

    // 4. Kalkulasi skor dari chain of responsibility
    int score = scoringRule.scoreHand(handToScore);

    // 5. Cek kondisi menang & uang
    bool win = blindRule.checkBlind(score);
    int reward = rewardRule.earnMoney(win, score);

    std::cout << "Money gained: " << reward << "\n";
    std::cout << "=== Round Ended ===\n";
}