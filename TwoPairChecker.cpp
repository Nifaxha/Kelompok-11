#include "TwoPairChecker.h"
#include "HandUtils.h"

HandRank TwoPairChecker::check(const Hand& hand) {
    if (HandUtils::isTwoPair(hand)) return HandRank::TWO_PAIR;
    return nextChecker ? nextChecker->check(hand) : HandRank::HIGH_CARD;
}