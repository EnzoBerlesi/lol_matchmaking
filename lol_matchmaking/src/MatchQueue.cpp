#include "MatchQueue.h"
#include <stdexcept>

MatchQueue::MatchQueue() : _front(nullptr), _back(nullptr), _size(0) {}

MatchQueue::~MatchQueue() {
    QueueNode* cur = _front;
    while (cur) {
        QueueNode* tmp = cur->next;
        delete cur;
        cur = tmp;
    }
}

void MatchQueue::enqueue(const Player& p) {
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
    QueueNode* cur = _front;
    while (cur) {
        if (cur->data.id == id) return true;
        cur = cur->next;
    }
    return false;
}

std::vector<Player> MatchQueue::peek() const {
    std::vector<Player> vec;
    QueueNode* cur = _front;
    while (cur) {
        vec.push_back(cur->data);
        cur = cur->next;
    }
    return vec;
}

std::vector<Player> MatchQueue::drainAll() {
    std::vector<Player> vec;
    while (!empty()) vec.push_back(dequeue());
    return vec;
}

void MatchQueue::refillFrom(const std::vector<Player>& vec) {
    for (const auto& p : vec) enqueue(p);
}
