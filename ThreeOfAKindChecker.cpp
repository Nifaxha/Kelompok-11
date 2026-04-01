#include "ThreeOfAKindChecker.h"
#include "HandUtils.h"

HandRank ThreeOfAKindChecker::check(const Hand& hand) {
    if (HandUtils::isThreeOfAKind(hand)) return HandRank::THREE_OF_A_KIND;
    return nextChecker ? nextChecker->check(hand) : HandRank::HIGH_CARD;
}