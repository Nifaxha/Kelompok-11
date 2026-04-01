#include "FlushFiveChecker.h"
#include "HandUtils.h"

HandRank FlushFiveChecker::check(const Hand& hand) {
    if (HandUtils::isFlushFive(hand)) return HandRank::FLUSH_FIVE;
    return nextChecker ? nextChecker->check(hand) : HandRank::HIGH_CARD;
}