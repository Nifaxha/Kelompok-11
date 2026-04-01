#include "StraightChecker.h"
#include "HandUtils.h"

HandRank StraightChecker::check(const Hand& hand) {
    if (HandUtils::isStraight(hand)) return HandRank::STRAIGHT;
    return nextChecker ? nextChecker->check(hand) : HandRank::HIGH_CARD;
}