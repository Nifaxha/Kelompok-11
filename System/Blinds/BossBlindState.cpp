#include "BossBlindState.h"
#include "SmallBlindState.h"

std::string BossBlindState::getName() const { return "Boss Blind"; }
int BossBlindState::getTargetScore(int ante) const { return 600 * ante; }
int BossBlindState::getRewardMoney() const { return 5; }

PendingCommand BossBlindState::createSkipRewardCommand() const {
    // Gunakan timing Start sesuai dokumen
    return PendingCommand(CommandTiming::Start, true, nullptr); 
}

std::unique_ptr<BlindState> BossBlindState::nextState(int& ante) const {
    ante++; 
    return std::unique_ptr<SmallBlindState>(new SmallBlindState());
}