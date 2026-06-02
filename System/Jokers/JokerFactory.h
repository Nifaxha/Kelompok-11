#pragma once
#include "JokerType.h"
#include "../IScoring.h"

class JokerFactory {
public:
    // Fungsi ini bertugas "membungkus" scoring dasar dengan Joker secara dinamis
    static IScoring* createJoker(JokerType type, IScoring* baseScoring);
};
