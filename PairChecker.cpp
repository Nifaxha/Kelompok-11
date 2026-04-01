#include "PairChecker.h"
#include "HandUtils.h"

HandRank PairChecker::check(const Hand& hand) {
    if (HandUtils::isPair(hand)) return HandRank::PAIR;
    return nextChecker ? nextChecker->check(hand) : HandRank::HIGH_CARD;
}