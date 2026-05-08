#include <iostream>
using namespace std;

#include "Matchmaking.hpp"
#include "Player.hpp"

int main() {
    Player Player1 = Player(1, "Ana", 1250, 1);
    Player Player2 = Player(2, "Bruno", 1000, 2);
    Player Player3 = Player(3, "Carla", 1200, 3);
    Matchmaking m1 = Matchmaking();
    m1.insert(Player1);
    m1.insert(Player2);
    m1.insert(Player3);
    m1.printWaitingPlayers();
    m1.sortByScoreMerge();
    m1.printWaitingPlayers();

    return 0;
}