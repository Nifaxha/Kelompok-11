#include "JokerFactory.h"
#include "JollyJoker.h"
#include "SpadeJoker.h"
#include "GreedyJoker.h"

IScoring* JokerFactory::createJoker(JokerType type, IScoring* baseScoring) {
    switch (type) {
        case JokerType::JOLLY:  return new JollyJoker(baseScoring);
        case JokerType::SPADE:  return new SpadeJoker(baseScoring);
        case JokerType::GREEDY: return new GreedyJoker(baseScoring);
        default: return baseScoring;
    }
}