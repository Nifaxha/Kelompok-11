#include <iostream>
#include "GameManager.h"

void GameManager::runSession() {
    std::cout << "=== Balatro Clone Started ===\n";

    Hand generatedHand = handGenerator.generateHand();
    ChosenHand chosenHand = handPlayer.playHand(generatedHand);
    Hand handToScore = chosenHand.toHand();

    // --- PROSES DECORATOR JOKER ---
    // 1. Buat instansiasi kalkulator skor dasar
    IScoring* gameScoring = new ScoringRule();

    // 2. Bungkus secara bertumpuk (Membeli/Mengaktifkan Joker)
    gameScoring = new JollyJoker(gameScoring);   // Bungkus ke-1
    gameScoring = new SpadesJoker(gameScoring);  // Bungkus ke-2
    gameScoring = new GreedyJoker(gameScoring);  // Bungkus ke-3 (Paling luar)

    // 3. Jalankan kalkulasi (Panggilan akan mengalir dari Greedy -> Spades -> Jolly -> ScoringRule)
    int score = gameScoring->scoreHand(handToScore);

    // 4. Bersihkan memory
    delete gameScoring; 
    // ------------------------------

    bool win = blindRule.checkBlind(score);
    int reward = rewardRule.earnMoney(win, score);

    std::cout << "Money gained: " << reward << "\n";
    std::cout << "=== Round Ended ===\n";
}
}