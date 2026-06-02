#pragma once
#include "Player.h"
#include <vector>

// Nó da fila
struct QueueNode {
    Player      data;
    QueueNode*  next;

    explicit QueueNode(const Player& p) : data(p), next(nullptr) {}
};

// Fila FIFO — armazena jogadores que estão procurando partida
class MatchQueue {
public:
    MatchQueue();
    ~MatchQueue();

    void    enqueue(const Player& p);
    Player  dequeue();               // remove e retorna o da frente
    bool    empty() const;
    int     size() const;
    bool    containsId(int id) const;

    // Retorna cópia do conteúdo sem remover (para exibição)
    std::vector<Player> peek() const;

    // Drena todos de volta para um vector (usado quando a montagem falha)
    std::vector<Player> drainAll();

    // Reinsere um vector inteiro na fila (mesma ordem)
    void    refillFrom(const std::vector<Player>& vec);

private:
    QueueNode* _front;
    QueueNode* _back;
    int        _size;
};
