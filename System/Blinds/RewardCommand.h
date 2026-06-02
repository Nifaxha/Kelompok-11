#pragma once
#include <string>
#include <memory>
#include "RunSessionState.h"
#include "../Deck.h" // Tambahkan ini agar bisa mengakses Deck

// Sesuai dokumen wajib: Start, NextBlind, NextAnte
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
    
    // Tambahkan parameter Deck& agar command bisa memodifikasi deck
    virtual void execute(RunSessionState& state, Deck& deck) = 0; 
};

// --- Implementasi Command Spesifik Wajib ---
class BonusHandCommand : public RewardCommand {
public:
    std::string getName() const override { return "Bonus Hand"; }
    std::string getDescription() const override { return "Gain +1 hand next blind."; }
    void execute(RunSessionState& state, Deck& deck) override {
        state.remainingPlays += 1;
    }
};

class FreePlayingCard : public RewardCommand {
public:
    std::string getName() const override { return "Free Playing Card"; }
    std::string getDescription() const override { return "Gain free playing card, added to the deck."; }
    void execute(RunSessionState& state, Deck& deck) override {
        deck.addRandomCard(); // Kita akan tambahkan fungsi ini di Deck
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