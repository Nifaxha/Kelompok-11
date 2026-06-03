#pragma once

struct RunSessionState {
    int ante = 1;
    int remainingPlays = 4;
    int remainingDiscards = 3;
    int freeRerolls = 0;
    int playerMoney = 0;
    int extraHandSize = 0; // <--- TAMBAHAN: Menyimpan bonus hand size sementara
};