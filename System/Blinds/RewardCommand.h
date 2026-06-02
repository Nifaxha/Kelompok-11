#pragma once
#include <string>
#include <memory>
#include "RunSessionState.h"
#include "../Deck.h" // Tambahkan ini agar command bisa modifikasi deck

// Enum Timing diubah sesuai dokumen PDF
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
    
    // Tambahkan parameter Deck& 
    virtual void execute(RunSessionState& state, Deck& deck) = 0; 
};

// --- Implementasi Command ---
class BonusHandCommand : public RewardCommand {
public:
    std::string getName() const override { return "Bonus Hand"; }
    std::string getDescription() const override { return "Gain +1 hand next blind."; }
    void execute(RunSessionState& state, Deck& deck) override {
        state.remainingPlays += 1;
    }
};

// Ubah FreeReroll menjadi FreePlayingCard sesuai PDF
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