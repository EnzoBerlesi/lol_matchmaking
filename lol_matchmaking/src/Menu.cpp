#include "Menu.h"
#include "Reports.h"
#include <iostream>
#include <limits>
#include <algorithm>
#include <cctype>

namespace Menu {

// ── Utilitários ───────────────────────────────────────────────────────────────

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pauseConsole() {
    std::cout << "\nPressione [ENTER] para retornar ao Menu Principal...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void printHeader(const std::string& title) {
    std::string sep(68, '=');
    std::cout << "\n" << sep << "\n"
              << std::string((68 - (int)title.size()) / 2, ' ') << title << "\n"
              << sep << "\n";
}

// Lê role do console com validação
static Role readRole(const std::string& prompt) {
    while (true) {
        std::cout << prompt << " (TOP/JUNGLE/MID/ADC/SUPPORT): ";
        std::string s;
        std::cin >> s;
        std::transform(s.begin(), s.end(), s.begin(), ::toupper);
        Role r = stringToRole(s);
        if (r != Role::NONE) return r;
        std::cout << "  [!] Role invalida. Tente novamente.\n";
    }
}

// ── Handlers ──────────────────────────────────────────────────────────────────

void handleCadastrarJogador(PlayerList& players) {
    clearScreen();
    printHeader("CADASTRAR NOVO JOGADOR");

    Player p;
    p.id         = players.nextId();
    p.mmr        = 1000;
    p.wins       = 0;
    p.totalGames = 0;
    p.assignedRole = Role::NONE;

    std::cout << "Nome do jogador: ";
    std::cin >> p.name;

    // Verifica duplicata de nome
    if (players.findByName(p.name)) {
        std::cout << "\n[!] Ja existe um jogador com o nome \"" << p.name << "\".\n";
        pauseConsole();
        return;
    }

    p.primaryRole   = readRole("Role primaria  ");
    p.secondaryRole = readRole("Role secundaria");

    if (p.primaryRole == p.secondaryRole) {
        std::cout << "\n[!] As duas roles nao podem ser iguais.\n";
        pauseConsole();
        return;
    }

    players.addPlayer(p);
    std::cout << "\n[OK] Jogador \"" << p.name << "\" cadastrado com ID #"
              << p.id << " e MMR inicial de 1000.\n";
    pauseConsole();
}

void handleInserirNaFila(PlayerList& players, MatchQueue& queue) {
    clearScreen();
    printHeader("INSERIR JOGADOR NA FILA");

    std::cout << "Informe o Nome ou ID do jogador: ";
    std::string input;
    std::cin >> input;

    Player* p = nullptr;
    // Tenta interpretar como ID numérico primeiro
    bool isNum = !input.empty() && std::all_of(input.begin(), input.end(), ::isdigit);
    if (isNum) p = players.findById(std::stoi(input));
    if (!p)    p = players.findByName(input);

    if (!p) {
        std::cout << "\n[!] Jogador nao encontrado.\n";
        pauseConsole();
        return;
    }
    if (queue.containsId(p->id)) {
        std::cout << "\n[!] \"" << p->name << "\" ja esta na fila.\n";
        pauseConsole();
        return;
    }

    queue.enqueue(*p);
    std::cout << "\n[OK] \"" << p->name << "\" (MMR " << p->mmr
              << ") adicionado a fila. Posicao: " << queue.size() << "\n";
    pauseConsole();
}

void handleVisualizarFila(const MatchQueue& queue) {
    clearScreen();
    Reports::showQueue(queue);
    pauseConsole();
}

void handleFormarPartida(MatchQueue& queue, MatchStack& stack, Matchmaker& engine) {
    clearScreen();
    printHeader("FORMAR PARTIDA");
    engine.tryFormMatch(queue, stack);
    if (!stack.empty()) Reports::showLobby(stack);
    pauseConsole();
}

void handleResolverPartida(MatchStack& stack, PlayerList& players, Matchmaker& engine) {
    clearScreen();
    printHeader("RESOLVER PARTIDA DO TOPO");

    if (stack.empty()) {
        std::cout << "\n[!] Nao ha partidas pendentes.\n";
        pauseConsole();
        return;
    }

    Reports::showLobby(stack);

    std::cout << "\nO time acima venceu a partida simulada?\n"
              << "[1] Sim (Vitoria - MMR +" << Matchmaker::MMR_WIN  << ")\n"
              << "[0] Nao (Derrota - MMR " << Matchmaker::MMR_LOSS << ")\n"
              << "Escolha o resultado: ";
    int choice;
    std::cin >> choice;
    bool victory = (choice == 1);
    engine.resolveMatch(stack, players, victory);
    pauseConsole();
}

void handleBuscarEditar(PlayerList& players) {
    clearScreen();
    printHeader("BUSCAR / EDITAR JOGADOR");

    std::cout << "Informe o Nome ou ID: ";
    std::string input;
    std::cin >> input;

    Player* p = nullptr;
    bool isNum = !input.empty() && std::all_of(input.begin(), input.end(), ::isdigit);
    if (isNum) p = players.findById(std::stoi(input));
    if (!p)    p = players.findByName(input);

    if (!p) {
        std::cout << "\n[!] Jogador nao encontrado.\n";
        pauseConsole();
        return;
    }

    std::cout << "\n--- Dados Atuais ---\n"
              << "ID: "      << p->id
              << " | Nome: " << p->name
              << " | MMR: "  << p->mmr
              << " | WR: "   << p->winrateStr()
              << " | Primaria: "   << roleToString(p->primaryRole)
              << " | Secundaria: " << roleToString(p->secondaryRole)
              << "\n\n"
              << "O que deseja editar?\n"
              << "[1] MMR\n"
              << "[2] Vitorias\n"
              << "[3] Total de Partidas\n"
              << "[4] Roles\n"
              << "[0] Cancelar\n"
              << "Opcao: ";

    int opt;
    std::cin >> opt;
    switch (opt) {
        case 1:
            std::cout << "Novo MMR: ";
            std::cin >> p->mmr;
            std::cout << "[OK] MMR atualizado.\n";
            break;
        case 2:
            std::cout << "Novo total de vitorias: ";
            std::cin >> p->wins;
            std::cout << "[OK] Vitorias atualizadas.\n";
            break;
        case 3:
            std::cout << "Novo total de partidas: ";
            std::cin >> p->totalGames;
            std::cout << "[OK] Total de partidas atualizado.\n";
            break;
        case 4:
            p->primaryRole   = readRole("Nova role primaria  ");
            p->secondaryRole = readRole("Nova role secundaria");
            if (p->primaryRole == p->secondaryRole) {
                std::cout << "[!] Roles iguais — alteracao cancelada.\n";
            } else {
                std::cout << "[OK] Roles atualizadas.\n";
            }
            break;
        default:
            std::cout << "Cancelado.\n";
    }
    pauseConsole();
}

void handleRelatorioWinrate(const PlayerList& players) {
    clearScreen();
    printHeader("RANKING DE WINRATE POR POSICAO");

    Role role = readRole("Informe a posicao para o relatorio");
    Reports::winrateByRole(players, role);
    pauseConsole();
}

void handleRelatorioPopularidade(const PlayerList& players) {
    clearScreen();
    Reports::rolePopularity(players);
    pauseConsole();
}

// ── Loop principal ────────────────────────────────────────────────────────────

void run(PlayerList& players, MatchQueue& queue,
         MatchStack& stack, Matchmaker& engine)
{
    int choice = -1;
    while (choice != 0) {
        clearScreen();
        printHeader("LOL MATCHMAKER & RECOMENDACAO");
        std::cout
            << "1. Cadastrar Novo Jogador (Nome, Primaria e Secundaria)\n"
            << "2. Inserir Jogador na Fila de Busca\n"
            << "3. Visualizar Fila de Matchmaking Ativa\n"
            << "4. Formar Partida (Montar Time de 5 Jogadores)\n"
            << "5. Resolver Partida do Topo (Declarar Vitoria/Derrota)\n"
            << "6. Buscar / Editar Estatisticas de Jogador (Nome/ID)\n"
            << "7. Relatorio: Ranking de Winrate por Posicao (Merge Sort)\n"
            << "8. Relatorio: Estatisticas de Popularidade de Roles (Bubble Sort)\n"
            << "0. Sair do Programa\n"
            << std::string(68, '=') << "\n"
            << "Escolha uma opcao: ";
        std::cin >> choice;

        switch (choice) {
            case 1: handleCadastrarJogador(players);                           break;
            case 2: handleInserirNaFila(players, queue);                       break;
            case 3: handleVisualizarFila(queue);                               break;
            case 4: handleFormarPartida(queue, stack, engine);                 break;
            case 5: handleResolverPartida(stack, players, engine);             break;
            case 6: handleBuscarEditar(players);                               break;
            case 7: handleRelatorioWinrate(players);                           break;
            case 8: handleRelatorioPopularidade(players);                      break;
            case 0: std::cout << "\nSaindo do sistema. Ate mais!\n"; break;
            default: std::cout << "\n[!] Opcao invalida.\n"; pauseConsole();   break;
        }
    }
}

} // namespace Menu
