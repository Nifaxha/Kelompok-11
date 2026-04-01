#pragma once
#include <string>

enum class Suit {
    Hearts,
    Diamonds,
    Clubs,
    Spades
};

enum class Rank {
    TWO = 2,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING,
    ACE
};

struct Card {
    Rank rank;
    Suit suit;
};

std::string rankToString(Rank rank);
std::string suitToString(Suit suit);