#include "SmallBlindState.h"
#include "BigBlindState.h"

std::string SmallBlindState::getName() const { return "Small Blind"; }
int SmallBlindState::getTargetScore(int ante) const { return 300 * ante; }
int SmallBlindState::getRewardMoney() const { return 3; }

PendingCommand SmallBlindState::createSkipRewardCommand() const {
    return PendingCommand(
        CommandTiming::NextAnte, // Menggunakan timing wajib dari dokumen[cite: 12]
        false,
        std::unique_ptr<FreePlayingCard>(new FreePlayingCard()) // Memanggil FreePlayingCard[cite: 12]
    );
}

std::unique_ptr<BlindState> SmallBlindState::nextState(int& ante) const {
    return std::make_unique<BigBlindState>();
}