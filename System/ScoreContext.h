#pragma once

struct ScoreContext {
    int chips = 0;
    int mult = 0;

    // Fungsi bantuan untuk menghitung hasil akhir
    int getFinalScore() const {
        return chips * mult;
    }
};