#pragma once
#include "Player.h"
#include <vector>

// Lista encadeada simples que serve como "banco de dados" em memória
struct PlayerNode {
    Player      data;
    PlayerNode* next;

    explicit PlayerNode(const Player& p) : data(p), next(nullptr) {}
};

class PlayerList {
public:
    PlayerList();
    ~PlayerList();

    // CRUD
    void    addPlayer(const Player& p);
    Player* findById(int id);
    Player* findByName(const std::string& name);
    bool    updatePlayer(const Player& updated); // localiza por id e sobrescreve
    bool    removeById(int id);

    // Utilitários
    int     nextId() const;          // gera próximo ID sequencial
    int     size() const;
    bool    empty() const;

    // Copia todos os jogadores para um vector (útil para ordenação)
    std::vector<Player> toVector() const;

    // Atualiza todos de uma vez após ordenação (usado internamente)
    void    rebuildFromVector(const std::vector<Player>& vec);

    // Iteração simples
    PlayerNode* head() const { return _head; }

private:
    PlayerNode* _head;
    int         _size;
    int         _nextId;
};
