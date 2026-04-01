#include "FlushChecker.h"
#include "HandUtils.h"

HandRank FlushChecker::check(const Hand& hand) {
    if (HandUtils::isFlush(hand)) return HandRank::FLUSH;
    return nextChecker ? nextChecker->check(hand) : HandRank::HIGH_CARD;
}