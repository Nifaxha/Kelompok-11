#include <iostream>
#include "Shop.h"

void Shop::enterShop(int& playerMoney, std::vector<JokerType>& ownedJokers) {
    std::cout << "\n====================================\n";
    std::cout << "             WELCOME TO SHOP        \n";
    std::cout << "====================================\n";
    std::cout << "Uangmu saat ini: $" << playerMoney << "\n\n";

    std::cout << "[1] Jolly Joker  - $10 (Bonus Flat +20)\n";
    std::cout << "[2] Spade Joker  - $15 (Bonus +5 per kartu Sekop)\n";
    std::cout << "[3] Greedy Joker - $25 (Multiplier x2 jika Straight+)\n";
    std::cout << "[0] Keluar dari Toko\n";

    int pilihan;
    std::cout << "\nPilih Joker yang ingin dibeli: ";
    std::cin >> pilihan;

    if (pilihan == 1) {
        if (playerMoney >= 10) {
            playerMoney -= 10;
            ownedJokers.push_back(JokerType::JOLLY);
            std::cout << "Berhasil membeli Jolly Joker!\n";
        } else {
            std::cout << "Uang tidak cukup!\n";
        }
    } else if (pilihan == 2) {
        if (playerMoney >= 15) {
            playerMoney -= 15;
            ownedJokers.push_back(JokerType::SPADE);
            std::cout << "Berhasil membeli Spade Joker!\n";
        } else {
            std::cout << "Uang tidak cukup!\n";
        }
    } else if (pilihan == 3) {
        if (playerMoney >= 25) {
            playerMoney -= 25;
            ownedJokers.push_back(JokerType::GREEDY);
            std::cout << "Berhasil membeli Greedy Joker!\n";
        } else {
            std::cout << "Uang tidak cukup!\n";
        }
    } else {
        std::cout << "Keluar dari toko...\n";
    }
    std::cout << "====================================\n\n";
}