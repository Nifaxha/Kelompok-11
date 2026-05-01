#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include "HandGenerator.h"

Hand HandGenerator::generateHand() {
    std::cout << "Generating random hand...\n";
    Hand hand;
    std::vector<Card> deck;

    // Membuat 52 deck kartu standar
    char suits[] = {'H', 'D', 'C', 'S'};
    for (char suit : suits) {
        for (int rank = 2; rank <= 14; ++rank) {
            deck.push_back({rank, suit});
        }
    }

    // Mengacak deck (Shuffle)
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(deck.begin(), deck.end(), g);

    // Memberikan 8 kartu pertama ke pemain
    for (int i = 0; i < 8; ++i) {
        hand.cards.push_back(deck[i]);
    }

    return hand;
}