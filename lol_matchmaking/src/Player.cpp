#include "Player.h"
#include <sstream>
#include <iomanip>

// ── Conversões de Role ──────────────────────────────────────────────────────

std::string roleToString(Role r) {
    switch (r) {
        case Role::TOP:     return "TOP";
        case Role::JUNGLE:  return "JUNGLE";
        case Role::MID:     return "MID";
        case Role::ADC:     return "ADC";
        case Role::SUPPORT: return "SUPPORT";
        default:            return "NONE";
    }
}

Role stringToRole(const std::string& s) {
    if (s == "TOP"    || s == "top")     return Role::TOP;
    if (s == "JUNGLE" || s == "jungle")  return Role::JUNGLE;
    if (s == "MID"    || s == "mid")     return Role::MID;
    if (s == "ADC"    || s == "adc")     return Role::ADC;
    if (s == "SUPPORT"|| s == "support") return Role::SUPPORT;
    return Role::NONE;
}

// ── Player ──────────────────────────────────────────────────────────────────

double Player::winrate() const {
    if (totalGames == 0) return 0.0;
    return (static_cast<double>(wins) / totalGames) * 100.0;
}

std::string Player::winrateStr() const {
    if (totalGames == 0) return "0.0% (0/0 - Estreante)";
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(1) << winrate()
        << "% (" << wins << "/" << totalGames << ")";
    return oss.str();
}

std::string Player::display() const {
    // Formato do lobby: [ROLE]  - ID: XX | Nome: YYY | MMR: XXXX | WR: XX.X%
    std::ostringstream oss;
    std::string roleTag = "[" + roleToString(assignedRole) + "]";
    oss << std::left << std::setw(10) << roleTag
        << " - ID: " << std::setw(3) << id
        << " | Nome: " << std::setw(15) << name
        << " | MMR: " << std::setw(5) << mmr
        << " | WR: " << winrateStr();
    return oss.str();
}
