#include "SmallBlindState.h"
#include "BigBlindState.h"

std::string SmallBlindState::getName() const { return "Small Blind"; }
int SmallBlindState::getTargetScore(int ante) const { return 300 * ante; }
int SmallBlindState::getRewardMoney() const { return 3; }

PendingCommand SmallBlindState::createSkipRewardCommand() const {
    // Sesuai dokumen dan aman untuk C++11
    return PendingCommand(
        CommandTiming::NextAnte, 
        false,
        std::unique_ptr<FreePlayingCard>(new FreePlayingCard())
    );
}

std::unique_ptr<BlindState> SmallBlindState::nextState(int& ante) const {
    return std::unique_ptr<BigBlindState>(new BigBlindState());
}