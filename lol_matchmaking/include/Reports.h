#pragma once
#include "PlayerList.h"
#include "MatchQueue.h"
#include "MatchStack.h"
#include "Player.h"

namespace Reports {

    // Relatório 1: Ranking de winrate por posição (Merge Sort)
    void winrateByRole(const PlayerList& players, Role role);

    // Relatório 2: Popularidade de roles primárias (Bubble Sort)
    void rolePopularity(const PlayerList& players);

    // Exibe a fila de matchmaking atual
    void showQueue(const MatchQueue& queue);

    // Exibe o lobby (partida do topo da pilha)
    void showLobby(const MatchStack& stack);

} // namespace Reports
