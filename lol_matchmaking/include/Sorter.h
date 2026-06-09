#pragma once
#include "Player.h"
#include <vector>
#include <array>
#include <string>

namespace Sorter {

    // Regras de ordenação do sistema:
    // - Quick Sort por MMR: O(N log N), usado na busca rápida por nível de habilidade.
    // - Merge Sort por winrate: O(N log N) e estável, preserva a ordem de cadastro em empates.
    // - Ordenação do time: O(N²) é suficiente para o conjunto fixo de 5 jogadores por equipe.
    // - Popularidade de roles: O(N²) em conjunto pequeno e estático de 5 posições.

    // Quick Sort — ordena por MMR (usado antes de montar partida)
    void quickSortByMMR(std::vector<Player>& vec, int low, int high);

    // Merge Sort — ordena por winrate DESC (relatório por posição)
    void mergeSortByWinrate(std::vector<Player>& vec, int left, int right);

    // Ordenação do time: estratégia O(N²) para 5 jogadores, suficiente e simples para esse caso.
    void insertionSortByRole(std::array<Player,5>& team);

    // Bubble Sort — conta e ordena popularidade de roles primárias
    struct RoleCount { std::string roleName; int count; };
    std::array<RoleCount,5> bubbleSortRolePopularity(const std::vector<Player>& allPlayers);

}
