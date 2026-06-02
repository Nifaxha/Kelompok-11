#include "SmallBlindState.h"
#include "BigBlindState.h"

std::string SmallBlindState::getName() const { return "Small Blind"; }
int SmallBlindState::getTargetScore(int ante) const { return 300 * ante; }
int SmallBlindState::getRewardMoney() const { return 3; }

PendingCommand SmallBlindState::createSkipRewardCommand() const {
    return PendingCommand(
        CommandTiming::NextAnte, 
        false,
        // Dideklarasikan langsung sebagai tipe induknya (RewardCommand)
        std::unique_ptr<RewardCommand>(new FreePlayingCard())
    );
}

std::unique_ptr<BlindState> SmallBlindState::nextState(int& ante) const {
    // Dideklarasikan langsung sebagai tipe induknya (BlindState)
    return std::unique_ptr<BlindState>(new BigBlindState());

}

// Tambahkan fungsi tag ini
std::string SmallBlindState::getSkipRewardTag() const {
    return "Free Playing Card (Ditambahkan ke Deck di Ante berikutnya)";
}