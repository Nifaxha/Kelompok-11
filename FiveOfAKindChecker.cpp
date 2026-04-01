#include "FiveOfAKindChecker.h"
#include "HandUtils.h"

HandRank FiveOfAKindChecker::check(const Hand& hand) {
    if (HandUtils::isFiveOfAKind(hand)) return HandRank::FIVE_OF_A_KIND;
    return nextChecker ? nextChecker->check(hand) : HandRank::HIGH_CARD;
}