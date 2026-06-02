#include "MatchStack.h"
#include "Sorter.h"
#include <stdexcept>
#include <sstream>
#include <iomanip>

// ── Match::displayLobby ──────────────────────────────────────────────────────

std::string Match::displayLobby() const {
    std::ostringstream oss;
    std::string sep(68, '=');
    oss << sep << "\n"
        << std::setw(34) << "SAGUÃO ATIVO (LOBBY)" << "\n"
        << sep << "\n"
        << "Partida ID: #" << std::setfill('0') << std::setw(4) << id
        << std::setfill(' ')
        << " | Status: " << (resolved ? "ENCERRADA" : "AGUARDANDO RESULTADO")
        << "\n\n";

    // time já ordenado por role via Insertion Sort (Top→Sup)
    for (const auto& p : team) {
        oss << p.display() << "\n";
    }
    oss << std::string(68, '-') << "\n";
    return oss.str();
}

// ── MatchStack ───────────────────────────────────────────────────────────────

MatchStack::MatchStack() : _top(nullptr), _size(0), _nextId(1000) {}

MatchStack::~MatchStack() {
    MatchNode* cur = _top;
    while (cur) {
        MatchNode* tmp = cur->next;
        delete cur;
        cur = tmp;
    }
}

void MatchStack::push(const Match& m) {
    MatchNode* node = new MatchNode(m);
    node->next = _top;
    _top = node;
    ++_size;
    ++_nextId;
}

Match MatchStack::pop() {
    if (empty()) throw std::runtime_error("Pilha de partidas vazia");
    MatchNode* tmp = _top;
    Match m = tmp->data;
    _top = _top->next;
    delete tmp;
    --_size;
    return m;
}

Match& MatchStack::top() {
    if (empty()) throw std::runtime_error("Pilha de partidas vazia");
    return _top->data;
}

const Match& MatchStack::top() const {
    if (empty()) throw std::runtime_error("Pilha de partidas vazia");
    return _top->data;
}

bool MatchStack::empty() const { return _size == 0; }
int  MatchStack::size()  const { return _size; }

std::vector<Match> MatchStack::toVector() const {
    std::vector<Match> vec;
    MatchNode* cur = _top;
    while (cur) {
        vec.push_back(cur->data);
        cur = cur->next;
    }
    return vec;
}
