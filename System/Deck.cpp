#include <random>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include "Deck.h"

Deck::Deck() {
    resetAndShuffle();
}

void Deck::resetAndShuffle() {
    drawPile.clear();
    char suits[] = {'H', 'D', 'C', 'S'};
    for (char suit : suits) {
        for (int rank = 2; rank <= 14; ++rank) {
            drawPile.push_back({rank, suit});
        }
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(drawPile.begin(), drawPile.end(), g);
    std::cout << "[SISTEM] Deck baru berisi 52 kartu telah diacak.\n";
}

Card Deck::drawCard() {
    if (drawPile.empty()) {
        throw std::out_of_range("Deck habis!");
    }
    Card drawn = drawPile.back();
    drawPile.pop_back();
    return drawn;
}

bool Deck::isEmpty() const { return drawPile.empty(); }
int Deck::remainingCards() const { return drawPile.size(); }

void Deck::addRandomCard() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> rankDist(2, 14);
    char suits[] = {'H', 'D', 'C', 'S'};
    std::uniform_int_distribution<> suitDist(0, 3);
    
    drawPile.push_back({rankDist(gen), suits[suitDist(gen)]});
    std::cout << "[SISTEM] 1 Kartu acak telah ditambahkan ke dalam Deck (Reward)!\n";
}