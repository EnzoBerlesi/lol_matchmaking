#pragma once
#include "Player.h"
#include <vector>
#include <array>
#include <string>

namespace Sorter {

    // Quick Sort — ordena por MMR (usado antes de montar partida)
    void quickSortByMMR(std::vector<Player>& vec, int low, int high);

    // Merge Sort — ordena por winrate DESC (relatório por posição)
    void mergeSortByWinrate(std::vector<Player>& vec, int left, int right);

    // Insertion Sort — ordena 5 jogadores por ordem de role (Top→Sup)
    void insertionSortByRole(std::array<Player,5>& team);

    // Bubble Sort — conta e ordena popularidade de roles primárias
    struct RoleCount { std::string roleName; int count; };
    std::array<RoleCount,5> bubbleSortRolePopularity(const std::vector<Player>& allPlayers);

} // namespace Sorter
