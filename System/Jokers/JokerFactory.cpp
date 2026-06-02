#include "JokerFactory.h"
#include "BasicJoker.h"
#include "SpadeJoker.h"
#include "GreedyJoker.h"

IScoring* JokerFactory::createJoker(JokerType type, IScoring* baseScoring) {
    switch (type) {
        case JokerType::BASIC:  return new BasicJoker(baseScoring);
        case JokerType::SPADE:  return new SpadeJoker(baseScoring);
        case JokerType::GREEDY: return new GreedyJoker(baseScoring);
        default: return baseScoring;
    }
}