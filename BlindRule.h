#pragma once

class BlindRule {
private:
    int targetScore;

public:
    explicit BlindRule(int target = 50);
    bool checkBlind(int score);
};