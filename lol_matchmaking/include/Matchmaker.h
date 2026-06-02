#pragma once
#include "MatchQueue.h"
#include "MatchStack.h"
#include "PlayerList.h"
#include <optional>

// Motor de montagem de partidas
class Matchmaker {
public:
    // Tenta montar um time de 5 com roles distintas a partir da fila.
    // Retorna true se conseguiu montar e empilhar a partida.
    // Regra: ordena a fila por MMR (Quick Sort), depois distribui roles
    // tentando primária primeiro, secundária depois.
    bool tryFormMatch(MatchQueue& queue, MatchStack& stack);

    // Resolve a partida do topo: atualiza MMR (+25 vitória / -25 derrota)
    // e winrate de todos os 5 jogadores no PlayerList.
    void resolveMatch(MatchStack& stack, PlayerList& players, bool victory);

    // MMR delta configurável
    static constexpr int MMR_WIN  = +25;
    static constexpr int MMR_LOSS = -25;

private:
    // Tenta encaixar players nos 5 slots de role.
    // Retorna array preenchido ou nullopt se impossível.
    std::optional<std::array<Player,5>>
    assignRoles(std::vector<Player>& candidates);
};
