#include "BossBlindState.h"
#include "SmallBlindState.h"

std::string BossBlindState::getName() const { return "Boss Blind"; }
int BossBlindState::getTargetScore(int ante) const { return 600 * ante; }
int BossBlindState::getRewardMoney() const { return 5; }

// Boss Blind umumnya tidak bisa di-skip
PendingCommand BossBlindState::createSkipRewardCommand() const {
    return PendingCommand{ CommandTiming::Immediate, true, nullptr }; 
}

std::unique_ptr<BlindState> BossBlindState::nextState(int& ante) const {
    ante++; // Boss Blind menaikkan level Ante
    return std::make_unique<SmallBlindState>();
}