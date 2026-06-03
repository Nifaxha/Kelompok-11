#include <iostream>
#include <vector>
#include "GameManager.h"
#include "Jokers/JokerFactory.h"
#include "Blinds/SmallBlindState.h"
#include "IObserver.h" // WAJIB ADA AGAR GAME MENGENALI OBSERVER

GameManager::GameManager() {
    sessionState.ante = 1;
    sessionState.playerMoney = 0;
    currentBlind = std::unique_ptr<BlindState>(new SmallBlindState());
}

void GameManager::executePendingCommands(CommandTiming timing, Deck& currentDeck) {
    for (auto& pending : pendingCommands) {
        if (!pending.executed && pending.timing == timing && pending.command != nullptr) {
            std::cout << "[REWARD TERPICU] Mengeksekusi: " << pending.command->getName() << "\n";
            pending.command->execute(sessionState, currentDeck); 
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
        sessionState.extraHandSize = 0;

        executePendingCommands(CommandTiming::NextBlind, deck);

        int targetScore = currentBlind->getTargetScore(sessionState.ante);
        int totalRoundScore = 0;

        // 1. Tawarkan Menu Skip
        char menuAwal;
        std::cout << "\nTarget Skor: " << targetScore << " | Hadiah: $" << currentBlind->getRewardMoney() << "\n";
        std::cout << "Tag Skip   : [" << currentBlind->getSkipRewardTag() << "]\n";
        std::cout << "Aksi: [P]lay Blind | [S]kip Blind\n";
        std::cout << "Pilihanmu: ";
        std::cin >> menuAwal;
        std::cin.ignore();

        if (menuAwal == 'S' || menuAwal == 's') {
            PendingCommand skipReward = currentBlind->createSkipRewardCommand();
            if (skipReward.command != nullptr) {
                std::cout << "[SISTEM] Kamu melakukan Skip! Menambahkan antrean reward: " << skipReward.command->getName() << "\n";
                pendingCommands.push_back(std::move(skipReward));
                
                int oldAnte = sessionState.ante;
                currentBlind = currentBlind->nextState(sessionState.ante);
                if (sessionState.ante > oldAnte) {
                    executePendingCommands(CommandTiming::NextAnte, deck);
                }
                continue; // Lanjut ke iterasi blind berikutnya
            } else {
                std::cout << "[SISTEM] Blind ini tidak bisa di-skip!\n";
            }
        }

        // ========================================================
        // --- LAHIRKAN JOKER DI SINI (SEBELUM INNER LOOP) ---
        // ========================================================
        ScoringRule baseScoringRule;
        IScoring* scoringSystem = &baseScoringRule;
        std::vector<IScoring*> activeJokers; 

        for (JokerType jt : ownedJokers) {
            scoringSystem = JokerFactory::createJoker(jt, scoringSystem);
            activeJokers.push_back(scoringSystem);

            // Jika Joker ini adalah seorang Observer, pasang telinganya ke HandState
            if (IObserver* obs = dynamic_cast<IObserver*>(scoringSystem)) {
                handState.addObserver(obs); 
            }
        }

        // 2. Setup Permainan Jika Tidak Di-Skip
        deck.resetAndShuffle();
        handState.clearHand();
        handState.drawFromDeck(deck, 8 + sessionState.extraHandSize);
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
                    
                    // --- NOTIFIKASI OBSERVER SAAT DISCARD DITEKAN ---
                    handState.notifyObservers("DISCARD");
                    
                    handState.drawFromDeck(deck, 8 + sessionState.extraHandSize);
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

                // -> Evaluasi skor menggunakan Joker yang sudah menempel di awal ronde
                ScoreContext finalContext = scoringSystem->scoreHand(handToScore);
                int scoreThisHand = finalContext.getFinalScore();
                
                std::cout << "\n--- HASIL PLAY ---\n";
                std::cout << "Chips: " << finalContext.chips << " x Mult: " << finalContext.mult << "\n";
                std::cout << "Skor: " << scoreThisHand << "\n------------------\n";

                totalRoundScore += scoreThisHand;

                if (totalRoundScore >= targetScore) {
                    win = true;
                } else if (sessionState.remainingPlays > 0) {
                    handState.drawFromDeck(deck, 8 + sessionState.extraHandSize);
                }
            }
        } // Akhir Inner Loop

        // ========================================================
        // --- BERSIHKAN MEMORI JOKER & TELINGA OBSERVER ---
        // ========================================================
        for (IScoring* j : activeJokers) { 
            delete j; 
        }
        activeJokers.clear();
        handState.clearObservers(); 

        // 4. Evaluasi Akhir Ronde
        if (win) {
            std::cout << "\n[SISTEM] BLIND DEFEATED! (" << totalRoundScore << " / " << targetScore << ")\n";
            
            sessionState.playerMoney += currentBlind->getRewardMoney(); 
            sessionState.playerMoney += sessionState.remainingPlays;    
            
            std::cout << "Mendapat bonus sisa Play: +$" << sessionState.remainingPlays << "\n";
            std::cout << "Dompetmu sekarang: $" << sessionState.playerMoney << "\n";
            
            executePendingCommands(CommandTiming::NextBlind, deck); 
            
            shop.enterShop(sessionState.playerMoney, ownedJokers);
            
            int oldAnte = sessionState.ante;
            currentBlind = currentBlind->nextState(sessionState.ante);
            
            if (sessionState.ante > oldAnte) {
                executePendingCommands(CommandTiming::NextAnte, deck);
            }
        } else {
            std::cout << "\n[SISTEM] GAME OVER! Skor " << totalRoundScore << " tidak mencapai " << targetScore << ".\n";
            keepPlaying = false;
        }
    }
}