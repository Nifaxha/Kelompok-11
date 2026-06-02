#include <iostream>
#include "Shop.h"

void Shop::enterShop(int& playerMoney, std::vector<JokerType>& ownedJokers) {
    std::cout << "\n====================================\n";
    std::cout << "          🛒 SHOP / TOKO 🛒         \n";
    std::cout << "====================================\n";
    std::cout << "Dompetmu: $" << playerMoney << "\n\n";

    std::cout << "[1] Jolly Joker  - $15 (+8 Multiplier)\n";
    std::cout << "[2] Spade Joker  - $20 (+4 Mult per kartu Sekop)\n";
    std::cout << "[3] Greedy Joker - $35 (Mult x2 jika Chips >= 30)\n";
    std::cout << "[0] Keluar Toko (Lanjut ke Blind Berikutnya)\n";

    int pilihan;
    std::cout << "\nPilih item: ";
    std::cin >> pilihan;

    if (pilihan == 1 && playerMoney >= 15) {
        playerMoney -= 15;
        ownedJokers.push_back(JokerType::JOLLY);
        std::cout << "Berhasil membeli Jolly Joker!\n";
    } else if (pilihan == 2 && playerMoney >= 20) {
        playerMoney -= 20;
        ownedJokers.push_back(JokerType::SPADE);
        std::cout << "Berhasil membeli Spade Joker!\n";
    } else if (pilihan == 3 && playerMoney >= 35) {
        playerMoney -= 35;
        ownedJokers.push_back(JokerType::GREEDY);
        std::cout << "Berhasil membeli Greedy Joker!\n";
    } else if (pilihan != 0) {
        std::cout << "Uang tidak cukup atau pilihan salah!\n";
    }
    std::cout << "Meninggalkan toko...\n";
}