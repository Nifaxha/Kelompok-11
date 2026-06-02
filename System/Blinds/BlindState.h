#pragma once
#include <string>
#include <memory>
#include "RewardCommand.h"

class BlindState {
public:
    virtual ~BlindState() = default;
    virtual std::string getName() const = 0;
    virtual int getTargetScore(int ante) const = 0;
    virtual int getRewardMoney() const = 0;
    
    // TAMBAHKAN BARIS INI: Wajibkan semua Blind punya Tag Skip
    virtual std::string getSkipRewardTag() const = 0; 
    
    virtual PendingCommand createSkipRewardCommand() const = 0;
    virtual std::unique_ptr<BlindState> nextState(int& ante) const = 0;
};