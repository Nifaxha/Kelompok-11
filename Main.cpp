#include <iostream>
#include "GameManager.h"
#include "Hand.h"
#include "HandRank.h"

std::string rankToString(Rank rank) {
    switch (rank) {
        case Rank::TWO:   return "2";
        case Rank::THREE: return "3";
        case Rank::FOUR:  return "4";
        case Rank::FIVE:  return "5";
        case Rank::SIX:   return "6";
        case Rank::SEVEN: return "7";
        case Rank::EIGHT: return "8";
        case Rank::NINE:  return "9";
        case Rank::TEN:   return "10";
        case Rank::JACK:  return "J";
        case Rank::QUEEN: return "Q";
        case Rank::KING:  return "K";
        case Rank::ACE:   return "A";
        default:          return "?";
    }
}

std::string suitToString(Suit suit) {
    switch (suit) {
        case Suit::Hearts:   return "H";
        case Suit::Diamonds: return "D";
        case Suit::Clubs:    return "C";
        case Suit::Spades:   return "S";
        default:             return "?";
    }
}

void printHand(const Hand& hand) {
    std::cout << "Hand: ";
    for (const auto& card : hand.cards) {
        std::cout << rankToString(card.rank) << suitToString(card.suit) << " ";
    }
    std::cout << "\n";
}

std::string handRankToString(HandRank rank) {
    switch (rank) {
        case HandRank::HIGH_CARD:        return "High Card";
        case HandRank::PAIR:             return "Pair";
        case HandRank::TWO_PAIR:         return "Two Pair";
        case HandRank::THREE_OF_A_KIND:  return "Three of a Kind";
        case HandRank::STRAIGHT:         return "Straight";
        case HandRank::FLUSH:            return "Flush";
        case HandRank::FULL_HOUSE:       return "Full House";
        case HandRank::FOUR_OF_A_KIND:   return "Four of a Kind";
        case HandRank::STRAIGHT_FLUSH:   return "Straight Flush";
        case HandRank::ROYAL_FLUSH:      return "Royal Flush";
        case HandRank::FIVE_OF_A_KIND:   return "Five of a Kind";
        case HandRank::FLUSH_HOUSE:      return "Flush House";
        case HandRank::FLUSH_FIVE:       return "Flush Five";
        default:                         return "Unknown";
    }
}

int main() {
    GameManager gameManager;
    gameManager.runSession();
    return 0;
}