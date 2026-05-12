#include <iostream>
#include <random>
#include <chrono>
using namespace std;
using namespace std::chrono;

#include "Matchmaking.hpp"
#include "Player.hpp"

int main() {
    std::random_device rd;

    std::mt19937 gen(rd());

    std::uniform_int_distribution<> dist(1, 100);

    Matchmaking m = Matchmaking();
    for (int i = 0; i < 50000; i++) {
        Player p = Player(i, "Gabriel", dist(gen), i);
        m.insert(p);
    }
    
    auto start = high_resolution_clock::now();

    m.sortByScoreMerge();

    auto end = high_resolution_clock::now();

    auto mergeTime = duration_cast<milliseconds>(end - start);

    m.shuffle();

    start = high_resolution_clock::now();

    m.sortByScoreInsertion();

    end = high_resolution_clock::now();

    auto insertionTime = duration_cast<milliseconds>(end-start);

    cout << "Merge Time: " << mergeTime.count() << endl;
    cout << "Insertion Time: " << insertionTime.count() << endl;
    
    return 0;

}