#pragma once
#include <string>
#include <iostream>
#include <memory>
#include "RunSessionState.h"
#include "../Deck.h" 

enum class CommandTiming {
    Start,
    NextBlind,
    NextAnte
};

class RewardCommand {
public:
    virtual ~RewardCommand() = default;
    virtual std::string getName() const = 0;
    virtual std::string getDescription() const = 0;
    
    virtual void execute(RunSessionState& state, Deck& deck) = 0; 
};

// --- Implementasi Command ---

// 1. Command yang sempat hilang (Digunakan oleh Big Blind)
class BonusHandCommand : public RewardCommand {
public:
    std::string getName() const override { return "Bonus Hand"; }
    std::string getDescription() const override { return "Gain +1 hand next blind."; }
    void execute(RunSessionState& state, Deck& deck) override {
        state.remainingPlays += 1;
    }
};

// 2. Command baru untuk ekstra kapasitas tangan (Digunakan oleh Small Blind)
class BonusHandSizeCommand : public RewardCommand {
public:
    std::string getName() const override { return "Bonus Hand Size"; }
    std::string getDescription() const override { return "+3 Hand Size for the next round only."; }
    void execute(RunSessionState& state, Deck& deck) override {
        state.extraHandSize += 3;
        std::cout << "[REWARD] Kapasitas Hand Size bertambah +3 untuk ronde ini!\n";
    }
};

// 3. Command kartu gratis (Bisa kamu gunakan jika ingin mengganti reward blind lain nanti)
class FreePlayingCard : public RewardCommand {
public:
    std::string getName() const override { return "Free Playing Card"; }
    std::string getDescription() const override { return "Gain free playing card, added to the deck."; }
    void execute(RunSessionState& state, Deck& deck) override {
        deck.addRandomCard(); 
    }
};

// Struktur Pembungkus Antrean Eksekusi Tertunda
struct PendingCommand {
    CommandTiming timing;
    bool executed;
    std::unique_ptr<RewardCommand> command;

    PendingCommand(CommandTiming t, bool e, std::unique_ptr<RewardCommand> c) 
        : timing(t), executed(e), command(std::move(c)) {}
};