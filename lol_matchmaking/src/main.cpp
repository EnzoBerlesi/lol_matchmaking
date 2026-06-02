#include "PlayerList.h"
#include "MatchQueue.h"
#include "MatchStack.h"
#include "Matchmaker.h"
#include "Menu.h"

int main() {
    PlayerList players;
    MatchQueue queue;
    MatchStack stack;
    Matchmaker engine;

    Menu::run(players, queue, stack, engine);
    return 0;
}
