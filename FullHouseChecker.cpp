#include "FullHouseChecker.h"
#include "HandUtils.h"

HandRank FullHouseChecker::check(const Hand& hand) {
    if (HandUtils::isFullHouse(hand)) return HandRank::FULL_HOUSE;
    return nextChecker ? nextChecker->check(hand) : HandRank::HIGH_CARD;
}