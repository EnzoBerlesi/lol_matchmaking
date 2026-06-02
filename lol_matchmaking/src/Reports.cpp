#include "Reports.h"
#include "MatchQueue.h"
#include "Sorter.h"
#include <iostream>
#include <iomanip>
#include <vector>

namespace Reports {

// ── Relatório 1: Winrate por Posição (Merge Sort) ─────────────────────────────

void winrateByRole(const PlayerList& players, Role role) {
    auto vec = players.toVector();

    // Filtra jogadores que têm a role como primária ou secundária
    std::vector<Player> filtered;
    for (const auto& p : vec)
        if (p.primaryRole == role || p.secondaryRole == role)
            filtered.push_back(p);

    if (filtered.empty()) {
        std::cout << "\n[!] Nenhum jogador cadastrado para esta posicao.\n";
        return;
    }

    Sorter::mergeSortByWinrate(filtered, 0, (int)filtered.size() - 1);

    std::string roleName = roleToString(role);
    std::string sep(68, '=');
    std::cout << "\n" << sep << "\n"
              << std::setw(38) << ("RANKING DE DESEMPENHO - ROTA: " + roleName) << "\n"
              << sep << "\n"
              << "(Classificacao estavel gerada pelo algoritmo Merge Sort)\n\n";

    // Cabeçalho
    std::cout << std::left
              << std::setw(5)  << "Rank"
              << std::setw(20) << "| Nome do Jogador"
              << std::setw(7)  << "| ID"
              << std::setw(7)  << "| MMR"
              << std::setw(22) << "| Vitorias/Partidas"
              << "| Winrate\n";
    std::cout << std::string(5,'-') << "+" << std::string(19,'-') << "+"
              << std::string(6,'-')  << "+" << std::string(6,'-')  << "+"
              << std::string(21,'-') << "+" << std::string(10,'-') << "\n";

    int rank = 1;
    for (const auto& p : filtered) {
        std::cout << std::left
                  << std::setw(2) << rank++ << "o"
                  << std::setw(3) << " | " << std::setw(16) << p.name
                  << " | " << std::setw(4) << p.id
                  << " | " << std::setw(5) << p.mmr
                  << " | " << std::setw(5) << p.wins << " / " << std::setw(8) << p.totalGames
                  << " | " << p.winrateStr() << "\n";
    }
    std::cout << std::string(5,'-') << "+" << std::string(19,'-') << "+"
              << std::string(6,'-')  << "+" << std::string(6,'-')  << "+"
              << std::string(21,'-') << "+" << std::string(10,'-') << "\n";
}

// ── Relatório 2: Popularidade de Roles (Bubble Sort) ─────────────────────────

void rolePopularity(const PlayerList& players) {
    auto vec = players.toVector();
    if (vec.empty()) {
        std::cout << "\n[!] Nenhum jogador cadastrado.\n";
        return;
    }

    auto ranking = Sorter::bubbleSortRolePopularity(vec);
    std::string sep(50, '=');
    std::cout << "\n" << sep << "\n"
              << std::setw(30) << "POPULARIDADE DE ROLES PRIMARIAS" << "\n"
              << sep << "\n"
              << "(Ordenado pelo algoritmo Bubble Sort)\n\n";

    int pos = 1;
    for (const auto& rc : ranking) {
        std::cout << pos++ << "o - " << std::setw(8) << rc.roleName
                  << " | " << rc.count << " jogador(es)\n";
    }
    std::cout << sep << "\n";
}

// ── Exibe fila de matchmaking ─────────────────────────────────────────────────

void showQueue(const MatchQueue& queue) {
    std::string sep(68, '=');
    std::cout << "\n" << sep << "\n"
              << std::setw(40) << "FILA DE MATCHMAKING ATIVA" << "\n"
              << sep << "\n";

    if (queue.empty()) {
        std::cout << "  [Fila vazia]\n";
    } else {
        auto vec = queue.peek();
        int pos = 1;
        for (const auto& p : vec) {
            std::cout << "  " << pos++ << ". ID: " << std::setw(3) << p.id
                      << " | " << std::setw(15) << p.name
                      << " | MMR: " << p.mmr
                      << " | Primaria: " << roleToString(p.primaryRole)
                      << " | Secundaria: " << roleToString(p.secondaryRole)
                      << "\n";
        }
    }
    std::cout << sep << "\n";
}

// ── Exibe lobby (topo da pilha) ───────────────────────────────────────────────

void showLobby(const MatchStack& stack) {
    if (stack.empty()) {
        std::cout << "\n[!] Nenhuma partida pendente no momento.\n";
        return;
    }
    std::cout << "\n" << stack.top().displayLobby();
}

} // namespace Reports
