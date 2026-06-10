#include "PlayerList.h"
#include "MatchQueue.h"
#include "MatchStack.h"
#include "Matchmaker.h"
#include "Menu.h"

// Popula a lista com jogadores de exemplo para testes imediatos criando seeds
static void seedPlayers(PlayerList &players)
{
    struct Seed
    {
        std::string name;
        Role primary, secondary;
        int mmr, wins, total;
    };

    Seed seeds[] = {
        {"peeps", Role::TOP, Role::MID, 1025, 11, 21},
        {"poops", Role::JUNGLE, Role::TOP, 1000, 0, 0},
        {"Falso", Role::MID, Role::ADC, 1150, 16, 25},
        {"Vo Corvo", Role::ADC, Role::SUPPORT, 1050, 10, 18},
        {"Sabour 67", Role::SUPPORT, Role::JUNGLE, 1075, 18, 31},
    };

    for (auto &s : seeds)
    {
        Player p;
        p.id = players.nextId();
        p.name = s.name;
        p.primaryRole = s.primary;
        p.secondaryRole = s.secondary;
        p.mmr = s.mmr;
        p.wins = s.wins;
        p.totalGames = s.total;
        p.assignedRole = Role::NONE;
        players.addPlayer(p);
    }
}

int main()
{
    PlayerList players;
    MatchQueue queue;
    MatchStack stack;
    Matchmaker engine;

    seedPlayers(players);

    Menu::run(players, queue, stack, engine);
    return 0;
}