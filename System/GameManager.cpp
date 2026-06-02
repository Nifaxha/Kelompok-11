#include <iostream>
#include "GameManager.h"
#include "Jokers/JokerFactory.h"
#include "Blinds/SmallBlindState.h"

GameManager::GameManager() {
    sessionState.ante = 1;
    sessionState.playerMoney = 0;
    currentBlind = std::make_unique<SmallBlindState>(); // Mulai dari Small Blind
}

void GameManager::executePendingCommands(CommandTiming timing) {
    for (auto& pending : pendingCommands) {
        if (!pending.executed && pending.timing == timing && pending.command != nullptr) {
            std::cout << "[REWARD TERPICU] Mengeksekusi: " << pending.command->getName() << "\n";
            pending.command->execute(sessionState);
            pending.executed = true;
        }
    }
}

void GameManager::runSession() {
    std::cout << "=== Balatro Clone Started ===\n";
    bool keepPlaying = true;

    while (keepPlaying) {
        std::cout << "\n====================================\n";
        std::cout << "     ANTE " << sessionState.ante << " | " << currentBlind->getName() << "\n";
        std::cout << "====================================\n";

        // Reset resource standar untuk Blind baru
        sessionState.remainingPlays = 4;
        sessionState.remainingDiscards = 3;

        // Eksekusi efek tertunda yang aktif di Blind Baru (Contoh: Bonus Hand)
        executePendingCommands(CommandTiming::NextBlind);

        int targetScore = currentBlind->getTargetScore(sessionState.ante);
        int totalRoundScore = 0;

        // 1. Tawarkan Menu Skip (Kecuali Boss Blind yang mengembalikan nullptr/Immediate execute)
        char menuAwal;
        std::cout << "\nTarget Skor: " << targetScore << " | Hadiah: $" << currentBlind->getRewardMoney() << "\n";
        std::cout << "Aksi: [P]lay Blind | [S]kip Blind\n";
        std::cout << "Pilihanmu: ";
        std::cin >> menuAwal;
        std::cin.ignore();

        if (menuAwal == 'S' || menuAwal == 's') {
            PendingCommand skipReward = currentBlind->createSkipRewardCommand();
            if (skipReward.command != nullptr) {
                std::cout << "[SISTEM] Kamu melakukan Skip! Menambahkan antrean reward: " << skipReward.command->getName() << "\n";
                pendingCommands.push_back(std::move(skipReward));
                currentBlind = currentBlind->nextState(sessionState.ante);
                continue; // Lanjut ke iterasi blind berikutnya
            } else {
                std::cout << "[SISTEM] Blind ini tidak bisa di-skip!\n";
            }
        }

        // 2. Setup Permainan Jika Tidak Di-Skip
        deck.resetAndShuffle();
        handState.clearHand();
        handState.drawFromDeck(deck);
        bool win = false;

        // 3. INNER LOOP: Fase Permainan Kartu
        while (sessionState.remainingPlays > 0 && !win) {
            std::cout << "\n[ STATUS: " << currentBlind->getName() << " ]\n";
            std::cout << "Skor Saat Ini : " << totalRoundScore << " / " << targetScore << "\n";
            std::cout << "Sisa Play [" << sessionState.remainingPlays << "] | Sisa Discard [" << sessionState.remainingDiscards << "]\n";

            Hand currentHand = handState.getHandAsStruct();
            ChosenHand chosenHand = handPlayer.playHand(currentHand);

            char aksi;
            std::cout << "\nApakah kamu ingin [P]lay atau [D]iscard? (P/D): ";
            std::cin >> aksi;
            std::cin.ignore();

            if (aksi == 'D' || aksi == 'd') {
                if (sessionState.remainingDiscards > 0) {
                    handState.removePlayedCards(chosenHand);
                    std::cout << "[SISTEM] Membuang " << chosenHand.selectedCards.size() << " kartu.\n";
                    handState.drawFromDeck(deck);
                    sessionState.remainingDiscards--;
                } else {
                    std::cout << "[SISTEM] Discard habis!\n";
                }
                continue; 
            } 
            else if (aksi == 'P' || aksi == 'p') {
                Hand handToScore = chosenHand.toHand();
                handState.removePlayedCards(chosenHand);
                sessionState.remainingPlays--;

                IScoring* gameScoring = new ScoringRule();
                for (JokerType joker : ownedJokers) {
                    gameScoring = JokerFactory::createJoker(joker, gameScoring);
                }

                ScoreContext finalContext = gameScoring->scoreHand(handToScore);
                int scoreThisHand = finalContext.getFinalScore();
                
                std::cout << "\n--- HASIL PLAY ---\n";
                std::cout << "Chips: " << finalContext.chips << " x Mult: " << finalContext.mult << "\n";
                std::cout << "Skor: " << scoreThisHand << "\n------------------\n";

                totalRoundScore += scoreThisHand;
                delete gameScoring; 

                if (totalRoundScore >= targetScore) {
                    win = true;
                } else if (sessionState.remainingPlays > 0) {
                    handState.drawFromDeck(deck);
                }
            }
        } // Akhir Inner Loop

        // 4. Evaluasi Akhir Ronde
        if (win) {
            std::cout << "\n[SISTEM] BLIND DEFEATED! (" << totalRoundScore << " / " << targetScore << ")\n";
            sessionState.playerMoney += currentBlind->getRewardMoney(); 
            
            // Eksekusi reward tertunda untuk Shop (Contoh: Free Reroll)
            executePendingCommands(CommandTiming::NextShop);
            
            shop.enterShop(sessionState.playerMoney, ownedJokers);
            
            // Transisi ke State Berikutnya
            int oldAnte = sessionState.ante;
            currentBlind = currentBlind->nextState(sessionState.ante);
            
            if (sessionState.ante > oldAnte) {
                executePendingCommands(CommandTiming::NextAnte);
            }
        } else {
            std::cout << "\n[SISTEM] GAME OVER! Skor " << totalRoundScore << " tidak mencapai " << targetScore << ".\n";
            keepPlaying = false;
            continue;
        }

        char pilihanLanjut;
        std::cout << "Lanjut bermain? (y/n): ";
        std::cin >> pilihanLanjut;
        std::cin.ignore(); 
        if (pilihanLanjut == 'n' || pilihanLanjut == 'N') keepPlaying = false;
    }
}