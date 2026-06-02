#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include "HandPlayer.h"

ChosenHand HandPlayer::playHand(const Hand& hand) {
    std::cout << "\n====================================\n";
    std::cout << "          KARTU DI TANGANMU         \n";
    std::cout << "====================================\n";
    
    // Tampilkan 8 kartu
    for (size_t i = 0; i < hand.cards.size(); ++i) {
        std::string rankStr = std::to_string(hand.cards[i].rank);
        if (hand.cards[i].rank == 11) rankStr = "J";
        else if (hand.cards[i].rank == 12) rankStr = "Q";
        else if (hand.cards[i].rank == 13) rankStr = "K";
        else if (hand.cards[i].rank == 14) rankStr = "A";

        std::cout << "[" << i + 1 << "] Rank: " << rankStr << "\t Suit: " << hand.cards[i].suit << "\n";
    }

    ChosenHand chosen;
    std::vector<int> selectedIndices;
    std::string input;

    // Loop meminta input sampai valid
    while (true) {
        std::cout << "\nPilih maksimal 5 kartu untuk dimainkan!\n";
        std::cout << "(Masukkan nomor kartu dipisah spasi, contoh: 1 3 4 5 8): ";
        
        std::getline(std::cin, input);
        std::stringstream ss(input);
        int index;
        selectedIndices.clear();

        // Parse input dari user
        while (ss >> index) {
            // Pastikan angka valid (1 sampai 8) dan tidak duplikat
            if (index >= 1 && index <= hand.cards.size()) {
                if (std::find(selectedIndices.begin(), selectedIndices.end(), index) == selectedIndices.end()) {
                    selectedIndices.push_back(index);
                }
            }
        }

        // Validasi aturan: minimal 1, maksimal 5
        if (selectedIndices.empty()) {
            std::cout << "Kamu harus memilih minimal 1 kartu!\n";
        } else if (selectedIndices.size() > 5) {
            std::cout << "Terlalu banyak! Maksimal hanya 5 kartu.\n";
        } else {
            break; // Input sudah benar
        }
    }

    std::cout << "\n--- Kartu yang kamu mainkan ---\n";
    for (int idx : selectedIndices) {
        Card selectedCard = hand.cards[idx - 1]; // Kurangi 1 karena array mulai dari 0
        chosen.addCard(selectedCard);
        
        std::string rankStr = std::to_string(selectedCard.rank);
        if (selectedCard.rank == 11) rankStr = "J";
        else if (selectedCard.rank == 12) rankStr = "Q";
        else if (selectedCard.rank == 13) rankStr = "K";
        else if (selectedCard.rank == 14) rankStr = "A";

        std::cout << "-> Rank: " << rankStr << " Suit: " << selectedCard.suit << "\n";
    }
    std::cout << "-------------------------------\n\n";

    return chosen;
}