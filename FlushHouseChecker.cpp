#include "FlushHouseChecker.h"
#include "HandUtils.h"

HandRank FlushHouseChecker::check(const Hand& hand) {
    if (HandUtils::isFlushHouse(hand)) return HandRank::FLUSH_HOUSE;
    return nextChecker ? nextChecker->check(hand) : HandRank::HIGH_CARD;
}