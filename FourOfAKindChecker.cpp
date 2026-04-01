#include "FourOfAKindChecker.h"
#include "HandUtils.h"

HandRank FourOfAKindChecker::check(const Hand& hand) {
    if (HandUtils::isFourOfAKind(hand)) return HandRank::FOUR_OF_A_KIND;
    return nextChecker ? nextChecker->check(hand) : HandRank::HIGH_CARD;
}