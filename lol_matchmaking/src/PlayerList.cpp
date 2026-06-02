#include "PlayerList.h"
#include <algorithm>

PlayerList::PlayerList() : _head(nullptr), _size(0), _nextId(1) {}

PlayerList::~PlayerList() {
    PlayerNode* cur = _head;
    while (cur) {
        PlayerNode* tmp = cur->next;
        delete cur;
        cur = tmp;
    }
}

void PlayerList::addPlayer(const Player& p) {
    PlayerNode* node = new PlayerNode(p);
    // insere no fim para preservar ordem de cadastro
    if (!_head) {
        _head = node;
    } else {
        PlayerNode* cur = _head;
        while (cur->next) cur = cur->next;
        cur->next = node;
    }
    ++_size;
    if (p.id >= _nextId) _nextId = p.id + 1;
}

Player* PlayerList::findById(int id) {
    PlayerNode* cur = _head;
    while (cur) {
        if (cur->data.id == id) return &cur->data;
        cur = cur->next;
    }
    return nullptr;
}

Player* PlayerList::findByName(const std::string& name) {
    PlayerNode* cur = _head;
    while (cur) {
        if (cur->data.name == name) return &cur->data;
        cur = cur->next;
    }
    return nullptr;
}

bool PlayerList::updatePlayer(const Player& updated) {
    Player* p = findById(updated.id);
    if (!p) return false;
    *p = updated;
    return true;
}

bool PlayerList::removeById(int id) {
    if (!_head) return false;
    if (_head->data.id == id) {
        PlayerNode* tmp = _head;
        _head = _head->next;
        delete tmp;
        --_size;
        return true;
    }
    PlayerNode* cur = _head;
    while (cur->next) {
        if (cur->next->data.id == id) {
            PlayerNode* tmp = cur->next;
            cur->next = tmp->next;
            delete tmp;
            --_size;
            return true;
        }
        cur = cur->next;
    }
    return false;
}

int PlayerList::nextId() const { return _nextId; }
int PlayerList::size()   const { return _size; }
bool PlayerList::empty() const { return _size == 0; }

std::vector<Player> PlayerList::toVector() const {
    std::vector<Player> vec;
    vec.reserve(_size);
    PlayerNode* cur = _head;
    while (cur) {
        vec.push_back(cur->data);
        cur = cur->next;
    }
    return vec;
}

void PlayerList::rebuildFromVector(const std::vector<Player>& vec) {
    // Destrói lista atual
    PlayerNode* cur = _head;
    while (cur) {
        PlayerNode* tmp = cur->next;
        delete cur;
        cur = tmp;
    }
    _head = nullptr;
    _size = 0;
    _nextId = 1;
    for (const auto& p : vec) addPlayer(p);
}
