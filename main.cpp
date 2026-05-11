#include <iostream>
using namespace std;

#include "Matchmaking.hpp"
#include "Player.hpp"

int main() {
    Player Player1 = Player(1, "Ana", 1250, 1);
    Player Player2 = Player(2, "Bruno", 1000, 2);
    Player Player3 = Player(3, "Carla", 1200, 3);
    Player Player4 = Player(4, "Fernandinho" , 1200, 4);
    Matchmaking m1 = Matchmaking();
    m1.insert(Player1);
    m1.insert(Player2);
    m1.sortByScoreInsertion();
    m1.removePlayer(2);
    m1.insert(Player3);
    m1.insert(Player2);
    m1.insert(Player4);
    m1.printWaitingPlayers(); 
    m1.sortByScoreMerge();
    m1.untieByTimestamp();
    m1.printWaitingPlayers();
    int n;
    Player* waiting = m1.getWaitingPlayers(&n);
    cout << "n = " << n << endl;
    Player* group1 = m1.formGroup(3, 50, &n);
    cout << "n = " << n << endl;
    m1.printWaitingPlayers();
    delete[] group1;
    Player* group2 = m1.formGroup(3, 50, &n);
    cout << "n = " << n << endl;
    cout << waiting[0].getId() << waiting[1].getId() << waiting[2].getId() << waiting[3].getId() << endl;
    m1.printWaitingPlayers();
    return 0;
}