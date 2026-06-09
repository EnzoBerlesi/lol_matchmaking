#pragma once
#include "Player.h"
#include <array>
#include <vector>

// Uma partida formada com 5 jogadores, um por role.
struct Match {
    int                  id;
    std::array<Player,5> team;  // índice = Role (TOP=0..SUPPORT=4)
    bool                 resolved;
    bool                 victory;  // true = time venceu

    std::string displayLobby() const;
};

// Nó interno da pilha de partidas pendentes de resultado.
struct MatchNode {
    Match       data;
    MatchNode*  next;

    explicit MatchNode(const Match& m) : data(m), next(nullptr) {}
};

// Pilha LIFO: guarda as partidas ainda sem resultado, com a mais recente no topo.
class MatchStack {
public:
    MatchStack();
    ~MatchStack();

    void    push(const Match& m);
    Match   pop();
    Match&       top();
    const Match& top() const;
    bool    empty() const;
    int     size() const;

    // Histórico completo (do topo para baixo)
    std::vector<Match> toVector() const;

    int nextMatchId() const { return _nextId; }

private:
    MatchNode* _top;
    int        _size;
    int        _nextId;
};
