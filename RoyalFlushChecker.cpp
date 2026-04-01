#include "RoyalFlushChecker.h"
#include "HandUtils.h"

HandRank RoyalFlushChecker::check(const Hand& hand) {
    if (HandUtils::isRoyalFlush(hand)) return HandRank::ROYAL_FLUSH;
    return nextChecker ? nextChecker->check(hand) : HandRank::HIGH_CARD;
}