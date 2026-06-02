#include "Matchmaker.h"
#include "Sorter.h"
#include <iostream>
#include <array>
#include <algorithm>

// Tenta encaixar candidates (já ordenados por MMR) nos 5 slots de role.
// Estratégia: para cada slot de role (Top→Sup), procura o primeiro player
// disponível cujo primaryRole ou secondaryRole corresponda.
std::optional<std::array<Player, 5>>
Matchmaker::assignRoles(std::vector<Player>& candidates) {
    const Role roleOrder[5] = {
        Role::TOP, Role::JUNGLE, Role::MID, Role::ADC, Role::SUPPORT
    };
    std::array<Player, 5> team{};
    std::vector<bool> used(candidates.size(), false);

    // Passe 1: primária
    for (int slot = 0; slot < 5; ++slot) {
        for (int k = 0; k < (int)candidates.size(); ++k) {
            if (!used[k] && candidates[k].primaryRole == roleOrder[slot]) {
                team[slot] = candidates[k];
                team[slot].assignedRole = roleOrder[slot];
                used[k] = true;
                break;
            }
        }
    }
    // Passe 2: secundária para slots ainda vazios
    for (int slot = 0; slot < 5; ++slot) {
        if (team[slot].id != 0) continue;  // já preenchido
        for (int k = 0; k < (int)candidates.size(); ++k) {
            if (!used[k] && candidates[k].secondaryRole == roleOrder[slot]) {
                team[slot] = candidates[k];
                team[slot].assignedRole = roleOrder[slot];
                used[k] = true;
                break;
            }
        }
    }
    // Verifica se todos os 5 slots foram preenchidos
    for (int slot = 0; slot < 5; ++slot)
        if (team[slot].id == 0) return std::nullopt;

    return team;
}

bool Matchmaker::tryFormMatch(MatchQueue& queue, MatchStack& stack) {
    if (queue.size() < 5) {
        std::cout << "\n[!] Jogadores na fila insuficientes (minimo 5). "
                  << "Atualmente: " << queue.size() << "\n";
        return false;
    }

    // Drena a fila, ordena por MMR (Quick Sort) e tenta montar
    auto all = queue.drainAll();
    Sorter::quickSortByMMR(all, 0, (int)all.size() - 1);

    // Tenta pegar os 5 primeiros (MMR mais próximo)
    std::vector<Player> window(all.begin(), all.begin() + 5);
    auto result = assignRoles(window);

    if (!result) {
        // Roles incompatíveis — devolve todos para fila na ordem original
        queue.refillFrom(all);
        std::cout << "\n[!] Nao foi possivel montar partida: roles incompativeis "
                  << "entre os 5 jogadores de maior MMR na fila.\n"
                  << "    Adicione mais jogadores com roles diferentes.\n";
        return false;
    }

    // Ordena o time pelo Insertion Sort (Top→Jg→Mid→ADC→Sup)
    auto& team = *result;
    Sorter::insertionSortByRole(team);

    // Monta a partida e empilha
    Match m;
    m.id = stack.nextMatchId();
    m.team = team;
    m.resolved = false;
    m.victory  = false;
    stack.push(m);

    // Devolve os jogadores que sobraram (índice 5 em diante)
    if (all.size() > 5) {
        std::vector<Player> rest(all.begin() + 5, all.end());
        queue.refillFrom(rest);
    }

    std::cout << "\n[OK] Partida #" << m.id << " formada com sucesso!\n";
    return true;
}

void Matchmaker::resolveMatch(MatchStack& stack, PlayerList& players, bool victory) {
    if (stack.empty()) {
        std::cout << "\n[!] Nenhuma partida pendente.\n";
        return;
    }
    Match m = stack.pop();
    m.resolved = true;
    m.victory  = victory;

    int delta = victory ? MMR_WIN : MMR_LOSS;

    std::cout << "\n--- Atualizando jogadores ---\n";
    for (auto& p : m.team) {
        Player* stored = players.findById(p.id);
        if (!stored) continue;
        stored->mmr       = std::max(0, stored->mmr + delta);
        stored->totalGames++;
        if (victory) stored->wins++;

        std::cout << "  " << stored->name
                  << " -> MMR: " << stored->mmr
                  << " | WR: "   << stored->winrateStr() << "\n";
    }
}
