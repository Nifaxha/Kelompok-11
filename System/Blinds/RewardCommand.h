#pragma once
#include <string>
#include <memory>
#include "RunSessionState.h"

// Waktu kapan reward akan dieksekusi
enum class CommandTiming {
    Immediate,
    NextBlind,
    NextShop,
    NextAnte
};

class RewardCommand {
public:
    virtual ~RewardCommand() = default;
    virtual std::string getName() const = 0;
    virtual std::string getDescription() const = 0;
    virtual void execute(RunSessionState& state) = 0;
};

// --- Implementasi Command Spesifik ---
class BonusHandCommand : public RewardCommand {
public:
    std::string getName() const override { return "Bonus Hand"; }
    std::string getDescription() const override { return "Gain +1 hand next blind."; }
    void execute(RunSessionState& state) override {
        state.remainingPlays += 1;
    }
};

class FreeRerollCommand : public RewardCommand {
public:
    std::string getName() const override { return "Free Reroll"; }
    std::string getDescription() const override { return "Gain 1 free reroll next shop."; }
    void execute(RunSessionState& state) override {
        state.freeRerolls += 1;
    }
};

// Struktur Pembungkus Antrean Eksekusi Tertunda
struct PendingCommand {
    CommandTiming timing;
    bool executed;
    std::unique_ptr<RewardCommand> command;

    // Tambahkan constructor ini agar aman di semua versi C++
    PendingCommand(CommandTiming t, bool e, std::unique_ptr<RewardCommand> c) 
        : timing(t), executed(e), command(std::move(c)) {}
};