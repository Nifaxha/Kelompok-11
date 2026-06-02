#pragma once
#include <vector>
#include <memory>
#include "Deck.h"
#include "HandState.h"
#include "HandPlayer.h"
#include "ScoringRule.h"
#include "Jokers/JokerType.h"
#include "Jokers/Shop.h"
#include "ScoreContext.h"
#include "Blinds/RunSessionState.h"
#include "Blinds/BlindState.h"
#include "Blinds/RewardCommand.h"

class GameManager {
public:
    GameManager();
    void runSession();

private:
    Deck deck;
    HandState handState;
    HandPlayer handPlayer;
    ScoringRule scoringRule;
    Shop shop;

    std::vector<JokerType> ownedJokers;
    
    // Arsitektur Baru State
    RunSessionState sessionState;
    std::unique_ptr<BlindState> currentBlind;
    std::vector<PendingCommand> pendingCommands;

    void executePendingCommands(CommandTiming timing, Deck& currentDeck); // <--- UBAH BARIS INI
};