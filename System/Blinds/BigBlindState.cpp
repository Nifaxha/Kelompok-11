#include "BigBlindState.h"
#include "BossBlindState.h"

std::string BigBlindState::getName() const { return "Big Blind"; }
int BigBlindState::getTargetScore(int ante) const { return 500 * ante; }
int BigBlindState::getRewardMoney() const { return 4; }

PendingCommand BigBlindState::createSkipRewardCommand() const {
    // Ubah ke format constructor biasa agar tidak error
    return PendingCommand(
        CommandTiming::NextBlind,
        false,
        std::unique_ptr<BonusHandCommand>(new BonusHandCommand())
    );
}

std::unique_ptr<BlindState> BigBlindState::nextState(int& ante) const {
    return std::unique_ptr<BossBlindState>(new BossBlindState());
}