#include "Sorter.h"
#include <algorithm>

namespace Sorter {

// ── 1. Quick Sort por MMR (DESC) ─────────────────────────────────────────────

static int partitionMMR(std::vector<Player>& vec, int low, int high) {
    int pivot = vec[high].mmr;
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (vec[j].mmr >= pivot) {           // ordem decrescente
            ++i;
            std::swap(vec[i], vec[j]);
        }
    }
    std::swap(vec[i + 1], vec[high]);
    return i + 1;
}

void quickSortByMMR(std::vector<Player>& vec, int low, int high) {
    if (low < high) {
        int pi = partitionMMR(vec, low, high);
        quickSortByMMR(vec, low, pi - 1);
        quickSortByMMR(vec, pi + 1, high);
    }
}

// ── 2. Merge Sort por Winrate (DESC) ─────────────────────────────────────────

static void mergeWinrate(std::vector<Player>& vec, int left, int mid, int right) {
    std::vector<Player> L(vec.begin() + left,  vec.begin() + mid + 1);
    std::vector<Player> R(vec.begin() + mid + 1, vec.begin() + right + 1);
    int i = 0, j = 0, k = left;
    while (i < (int)L.size() && j < (int)R.size()) {
        if (L[i].winrate() >= R[j].winrate())   // estável: >= para empate manter ordem
            vec[k++] = L[i++];
        else
            vec[k++] = R[j++];
    }
    while (i < (int)L.size()) vec[k++] = L[i++];
    while (j < (int)R.size()) vec[k++] = R[j++];
}

void mergeSortByWinrate(std::vector<Player>& vec, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortByWinrate(vec, left, mid);
        mergeSortByWinrate(vec, mid + 1, right);
        mergeWinrate(vec, left, mid, right);
    }
}

// ── 3. Insertion Sort por Role (Top=0 … Support=4) ───────────────────────────

void insertionSortByRole(std::array<Player, 5>& team) {
    for (int i = 1; i < 5; ++i) {
        Player key = team[i];
        int j = i - 1;
        while (j >= 0 && static_cast<int>(team[j].assignedRole)
                       >  static_cast<int>(key.assignedRole)) {
            team[j + 1] = team[j];
            --j;
        }
        team[j + 1] = key;
    }
}

// ── 4. Bubble Sort por popularidade de role primária ─────────────────────────

std::array<RoleCount, 5> bubbleSortRolePopularity(const std::vector<Player>& allPlayers) {
    std::array<RoleCount, 5> counts = {{
        {"TOP",     0},
        {"JUNGLE",  0},
        {"MID",     0},
        {"ADC",     0},
        {"SUPPORT", 0}
    }};
    for (const auto& p : allPlayers) {
        int idx = static_cast<int>(p.primaryRole);
        if (idx >= 0 && idx < 5) counts[idx].count++;
    }
    // Bubble sort DESC por contagem
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4 - i; ++j)
            if (counts[j].count < counts[j + 1].count)
                std::swap(counts[j], counts[j + 1]);
    return counts;
}

} // namespace Sorter
