#include "MatchQueue.h"
#include <stdexcept>

// Implementação da fila FIFO usada para guardar os jogadores na ordem de chegada.
// A estrutura permite inspecionar, esvaziar e restaurar os elementos sem perder a ordem.
MatchQueue::MatchQueue() : _front(nullptr), _back(nullptr), _size(0) {}

MatchQueue::~MatchQueue() {
    // Libera todos os nós alocados dinamicamente antes de destruir a fila.
    QueueNode* cur = _front;
    while (cur) {
        QueueNode* tmp = cur->next;
        delete cur;
        cur = tmp;
    }
}

void MatchQueue::enqueue(const Player& p) {
    // Insere sempre no fim para manter o comportamento FIFO.
    QueueNode* node = new QueueNode(p);
    if (!_back) {
        _front = _back = node;
    } else {
        _back->next = node;
        _back = node;
    }
    ++_size;
}

Player MatchQueue::dequeue() {
    if (empty()) throw std::runtime_error("Fila vazia");
    // Remove sempre da frente, respeitando a ordem de chegada.
    QueueNode* tmp = _front;
    Player p = tmp->data;
    _front = _front->next;
    if (!_front) _back = nullptr;
    delete tmp;
    --_size;
    return p;
}

bool MatchQueue::empty() const { return _size == 0; }
int  MatchQueue::size()  const { return _size; }

bool MatchQueue::containsId(int id) const {
    // Percorre a fila sem alterá-la para checar se o jogador já está aguardando.
    QueueNode* cur = _front;
    while (cur) {
        if (cur->data.id == id) return true;
        cur = cur->next;
    }
    return false;
}

std::vector<Player> MatchQueue::peek() const {
    // Copia os elementos para exibição sem remover ninguém da fila.
    std::vector<Player> vec;
    QueueNode* cur = _front;
    while (cur) {
        vec.push_back(cur->data);
        cur = cur->next;
    }
    return vec;
}

std::vector<Player> MatchQueue::drainAll() {
    // Esvazia a fila e devolve os jogadores na mesma ordem em um vector.
    std::vector<Player> vec;
    while (!empty()) vec.push_back(dequeue());
    return vec;
}

void MatchQueue::refillFrom(const std::vector<Player>& vec) {
    // Reinsere os jogadores preservando a ordem original recebida.
    for (const auto& p : vec) enqueue(p);
}
