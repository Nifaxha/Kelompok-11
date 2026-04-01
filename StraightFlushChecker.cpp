#include "StraightFlushChecker.h"
#include "HandUtils.h"

HandRank StraightFlushChecker::check(const Hand& hand) {
    if (HandUtils::isStraightFlush(hand)) return HandRank::STRAIGHT_FLUSH;
    return nextChecker ? nextChecker->check(hand) : HandRank::HIGH_CARD;
}