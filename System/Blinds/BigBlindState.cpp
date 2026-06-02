#include "BigBlindState.h"
#include "BossBlindState.h"

std::string BigBlindState::getName() const { return "Big Blind"; }
int BigBlindState::getTargetScore(int ante) const { return 500 * ante; }
int BigBlindState::getRewardMoney() const { return 4; }

PendingCommand BigBlindState::createSkipRewardCommand() const {
    return PendingCommand(
        CommandTiming::NextBlind,
        false,
        // Dideklarasikan langsung sebagai tipe induknya (RewardCommand)
        std::unique_ptr<RewardCommand>(new BonusHandCommand())
    );
}

std::unique_ptr<BlindState> BigBlindState::nextState(int& ante) const {
    // Dideklarasikan langsung sebagai tipe induknya (BlindState)
    return std::unique_ptr<BlindState>(new BossBlindState());

// ... (biarkan fungsi lainnya tetap sama)

// Tambahkan fungsi tag ini
std::string BigBlindState::getSkipRewardTag() const {
    return "Bonus Hand (+1 Jatah Play di Blind berikutnya)";
}
}