#include <iostream>
#include "GameManager.h"
#include "Jokers/JokerFactory.h"

GameManager::GameManager() : playerMoney(0) {}

void GameManager::runSession() {
    std::cout << "=== Balatro Clone Started ===\n";
    bool keepPlaying = true;
    int round = 1;

    while (keepPlaying) {
        std::cout << "\n====================================\n";
        std::cout << "              ROUND " << round << "\n";
        std::cout << "====================================\n";

        // 1. Setup Awal Ronde (Reset Deck dan Tangan)
        deck.resetAndShuffle();
        handState.clearHand();
        handState.drawFromDeck(deck);

        // State Batas Bermain (4 Play, 3 Discard)
        int remainingPlays = 4;
        int remainingDiscards = 3;
        int totalRoundScore = 0;
        int targetScore = round * 500; // Contoh target skor yang makin naik tiap ronde
        bool win = false;

        // 2. INNER LOOP: Fase Aksi Pemain
        while (remainingPlays > 0 && !win) {
            std::cout << "\n[ STATUS RONDE " << round << " ]\n";
            std::cout << "Target Skor   : " << targetScore << "\n";
            std::cout << "Skor Saat Ini : " << totalRoundScore << "\n";
            std::cout << "Sisa Play [" << remainingPlays << "] | Sisa Discard [" << remainingDiscards << "]\n";

            // Tampilkan kartu dan minta pemain memilih kartunya
            Hand currentHand = handState.getHandAsStruct();
            ChosenHand chosenHand = handPlayer.playHand(currentHand);

            // Minta keputusan aksi (Play atau Discard)
            char aksi;
            std::cout << "\nApakah kamu ingin [P]lay atau [D]iscard kartu-kartu tersebut? (P/D): ";
            std::cin >> aksi;
            std::cin.ignore();

            if (aksi == 'D' || aksi == 'd') {
                if (remainingDiscards > 0) {
                    // MEKANIK DISCARD
                    handState.removePlayedCards(chosenHand);
                    std::cout << "[SISTEM] Kamu membuang " << chosenHand.selectedCards.size() << " kartu.\n";
                    handState.drawFromDeck(deck); // Tarik kartu pengganti
                    remainingDiscards--;
                } else {
                    std::cout << "[SISTEM] Sisa Discard kamu habis! Aksi dibatalkan.\n";
                }
                continue; // Ulangi loop untuk minta aksi lagi
            } 
            else if (aksi == 'P' || aksi == 'p') {
                // MEKANIK PLAY
                Hand handToScore = chosenHand.toHand();
                handState.removePlayedCards(chosenHand); // Hapus kartu yang dimainkan dari tangan
                remainingPlays--;

                // --- SISTEM SKOR DENGAN SCORECONTEXT & MULTIPLIER ---
                IScoring* gameScoring = new ScoringRule();
                for (JokerType joker : ownedJokers) {
                    gameScoring = JokerFactory::createJoker(joker, gameScoring);
                }

                ScoreContext finalContext = gameScoring->scoreHand(handToScore);
                int scoreThisHand = finalContext.getFinalScore();
                
                std::cout << "\n--- HASIL PLAY ---\n";
                std::cout << "Chips: " << finalContext.chips << " x Mult: " << finalContext.mult << "\n";
                std::cout << "Skor Didapat: " << scoreThisHand << "\n";
                std::cout << "------------------\n";

                totalRoundScore += scoreThisHand;
                delete gameScoring; 
                // -----------------------------

                // Cek menang atau tarik kartu baru
                if (totalRoundScore >= targetScore) {
                    win = true;
                } else if (remainingPlays > 0) {
                    handState.drawFromDeck(deck); // Hanya tarik kartu baru jika ronde belum selesai
                }
            } else {
                std::cout << "[SISTEM] Pilihan tidak valid, silakan ulangi.\n";
            }
        } // Akhir dari Inner Loop (Ronde selesai)

        // 3. Evaluasi Hasil Akhir Ronde
        std::cout << "\n====================================\n";
        if (win) {
            std::cout << "[SISTEM] TARGET TERCAPAI! (" << totalRoundScore << " / " << targetScore << ")\n";
            int reward = rewardRule.earnMoney(true, totalRoundScore); 
            playerMoney += reward + (remainingPlays * 2); // Tambahan bonus jika masih ada sisa Play
            
            std::cout << "Dompet Saat Ini: $" << playerMoney << "\n";
            shop.enterShop(playerMoney, ownedJokers);
        } else {
            std::cout << "[SISTEM] GAME OVER! Skor akhirmu " << totalRoundScore << ", gagal mencapai target " << targetScore << ".\n";
            keepPlaying = false; // Game over jika gagal
            continue;
        }

        char pilihanLanjut;
        std::cout << "Lanjut bermain ke ronde berikutnya? (y/n): ";
        std::cin >> pilihanLanjut;
        std::cin.ignore(); 

        if (pilihanLanjut == 'n' || pilihanLanjut == 'N') {
            keepPlaying = false;
        } else {
            round++;
        }
    }

    std::cout << "\n=== Sesi Berakhir ===\n";
}