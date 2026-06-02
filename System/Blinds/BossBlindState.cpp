#include "BossBlindState.h"
#include "SmallBlindState.h"

std::string BossBlindState::getName() const { return "Boss Blind"; }
int BossBlindState::getTargetScore(int ante) const { return 600 * ante; }
int BossBlindState::getRewardMoney() const { return 5; }

PendingCommand BossBlindState::createSkipRewardCommand() const {
    return PendingCommand(CommandTiming::Start, true, nullptr); 
}

std::unique_ptr<BlindState> BossBlindState::nextState(int& ante) const {
    ante++; 
    // Dideklarasikan langsung sebagai tipe induknya (BlindState)
    return std::unique_ptr<BlindState>(new SmallBlindState());

}

// Tambahkan fungsi tag ini
std::string BossBlindState::getSkipRewardTag() const {
    return "TIDAK ADA (Boss Blind tidak bisa di-skip!)";
}