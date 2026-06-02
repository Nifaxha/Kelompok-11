#include <iostream>
#include "GameManager.h"
#include "Jokers/JokerFactory.h"

GameManager::GameManager() : playerMoney(0) {
    // Memulai game dengan saldo awal $0
}

void GameManager::runSession() {
    std::cout << "=== Balatro Clone Started ===\n";
    bool keepPlaying = true;
    int round = 1;

    while (keepPlaying) {
        std::cout << "\n====================================\n";
        std::cout << "              ROUND " << round << "\n";
        std::cout << "====================================\n";

        // 1. Jalankan gameplay mekanik kartu
        Hand generatedHand = handGenerator.generateHand();
        ChosenHand chosenHand = handPlayer.playHand(generatedHand);
        Hand handToScore = chosenHand.toHand();

        // 2. SYSTEM ARCHITECTURE: Pasang kalkulator skor dasar
        IScoring* gameScoring = new ScoringRule();

        // 3. SYSTEM ARCHITECTURE: Gunakan Factory untuk membungkus dengan Joker milik pemain secara dinamis
        for (JokerType joker : ownedJokers) {
            gameScoring = JokerFactory::createJoker(joker, gameScoring);
        }

        // 4. Kalkulasi skor dari tumpukan rantai Decorator -> Chain of Responsibility
        int score = gameScoring->scoreHand(handToScore);
        
        // Selalu bersihkan memory alokasi runtime decorator setelah kalkulasi selesai
        delete gameScoring; 

        // 5. Evaluasi hasil akhir round
        bool win = blindRule.checkBlind(score);
        int reward = rewardRule.earnMoney(win, score);
        playerMoney += reward;

        std::cout << "Uang terkumpul dari round ini: $" << reward << "\n";
        std::cout << "Total Dompet Pemain: $" << playerMoney << "\n";

        // 6. MEKANIK SHOP: Masuk ke toko jika menang round ini
        if (win) {
            std::cout << "\n[SISTEM] Target terpenuhi! Kamu berhak masuk ke Toko.\n";
            shop.enterShop(playerMoney, ownedJokers);
        } else {
            std::cout << "\n[SISTEM] Gagal melewati target Blind. Tidak bisa mampir ke Toko.\n";
        }

        // Menu kendali loop game
        char pilihan;
        std::cout << "Lanjut bermain ke round berikutnya? (y/n): ";
        std::cin >> pilihan;
        std::cin.ignore(); // Membersihkan sisa buffer input enter

        if (pilihan == 'n' || pilihan == 'N') {
            keepPlaying = false;
        } else {
            round++;
        }
    }

    std::cout << "\n=== Game Over / Sesi Berakhir ===\n";
}