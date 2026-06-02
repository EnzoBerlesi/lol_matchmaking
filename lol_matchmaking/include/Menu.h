#pragma once
#include "PlayerList.h"
#include "MatchQueue.h"
#include "MatchStack.h"
#include "Matchmaker.h"

namespace Menu {

    void run(PlayerList& players, MatchQueue& queue,
             MatchStack& stack, Matchmaker& engine);

    // Sub-menus / handlers de cada opção
    void handleCadastrarJogador(PlayerList& players);
    void handleInserirNaFila(PlayerList& players, MatchQueue& queue);
    void handleVisualizarFila(const MatchQueue& queue);
    void handleFormarPartida(MatchQueue& queue, MatchStack& stack,
                             Matchmaker& engine);
    void handleResolverPartida(MatchStack& stack, PlayerList& players,
                               Matchmaker& engine);
    void handleBuscarEditar(PlayerList& players);
    void handleRelatorioWinrate(const PlayerList& players);
    void handleRelatorioPopularidade(const PlayerList& players);

    // Utilitários de console
    void clearScreen();
    void pauseConsole();
    void printHeader(const std::string& title);

} // namespace Menu
