#pragma once
#include <string>

// Cinco roles clássicos do LoL
enum class Role {
    TOP,
    JUNGLE,
    MID,
    ADC,
    SUPPORT,
    NONE  // usado quando role não foi atribuída ainda
};

std::string roleToString(Role r);
Role stringToRole(const std::string& s);

struct Player {
    int    id;
    std::string name;
    Role   primaryRole;
    Role   secondaryRole;
    int    mmr;
    int    wins;
    int    totalGames;

    // Role que foi atribuída na partida atual (preenchida pelo matchmaker)
    Role   assignedRole;

    double winrate() const;
    std::string winrateStr() const;
    std::string display() const; // linha formatada para exibição no lobby
};
