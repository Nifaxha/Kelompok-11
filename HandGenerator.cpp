#include "HandGenerator.h"

Hand HandGenerator::generateHand() {
    Hand hand;

    hand.cards = {
        {Rank::TEN,   Suit::Hearts},
        {Rank::JACK,  Suit::Hearts},
        {Rank::QUEEN, Suit::Hearts},
        {Rank::KING,  Suit::Hearts},
        {Rank::ACE,   Suit::Hearts}
    };

    return hand;
}