#ifndef MATCHMAKING_HPP
#define MATCHMAKING_HPP

#include <iostream>
using namespace std;
#include "Player.hpp"

const int MAX_PLAYERS = 100000;

class Matchmaking {

private:
    Player* players;
    int size;

public:

    Matchmaking();
    ~Matchmaking();

    bool insert(Player player);
    bool removePlayer(int id);

    void sortByScoreInsertion();
    void sortByScoreMerge();
    void untieByTimestamp();

    Player* formGroup(int groupSize, int delta, int* n);

    Player* getWaitingPlayers(int* n);

    void printWaitingPlayers();

    void mergeSort(int left, int right);
    void merge(int left, int mid, int right);
    void shuffle();
};

#endif