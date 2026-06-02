#include "SmallBlindState.h"
#include "BigBlindState.h"

std::string SmallBlindState::getName() const { return "Small Blind"; }
int SmallBlindState::getTargetScore(int ante) const { return 300 * ante; }
int SmallBlindState::getRewardMoney() const { return 3; }

PendingCommand SmallBlindState::createSkipRewardCommand() const {
    // Gunakan kurung biasa () dan std::unique_ptr(new ...)
    return PendingCommand(
        CommandTiming::NextShop,
        false,
        std::unique_ptr<FreeRerollCommand>(new FreeRerollCommand())
    );
}

std::unique_ptr<BlindState> SmallBlindState::nextState(int& ante) const {
    return std::make_unique<BigBlindState>();
}