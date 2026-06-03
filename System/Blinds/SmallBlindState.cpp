#include "SmallBlindState.h"
#include "BigBlindState.h"

std::string SmallBlindState::getName() const { return "Small Blind"; }
int SmallBlindState::getTargetScore(int ante) const { return 300 * ante; }
int SmallBlindState::getRewardMoney() const { return 3; }

std::string SmallBlindState::getSkipRewardTag() const {
    return "+3 Hand Size for the next round only.\nCan be stacked multiple times on the same round, each adding an additional +3 Hand size.";
}

PendingCommand SmallBlindState::createSkipRewardCommand() const {
    return PendingCommand(
        CommandTiming::NextBlind,  // Berubah menjadi NextBlind (Ronde berikutnya)
        false,
        // Berubah menjadi BonusHandSizeCommand
        std::unique_ptr<RewardCommand>(new BonusHandSizeCommand()) 
    );
}

std::unique_ptr<BlindState> SmallBlindState::nextState(int& ante) const {
    return std::unique_ptr<BlindState>(new BigBlindState());
}