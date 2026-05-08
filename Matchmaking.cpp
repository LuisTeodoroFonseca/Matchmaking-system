#include <iostream>
using namespace std;

#include "Player.hpp"
#include "Matchmaking.hpp"

Matchmaking::Matchmaking() {
    players = new Player[MAX_PLAYERS];
    size = 0;
}

Matchmaking::~Matchmaking() {
    delete[] players;
}

bool Matchmaking::insert(Player player) {
    if (size == MAX_PLAYERS) 
        return false;
    players[size] = player;
    size++;
    return true;
}

bool Matchmaking::removePlayer(int id) {
    for(int i = 0; i < size; i++) {
        if(players[i].getId() == id){
            size--;
            for(int j = i; j < size; j++) {
                players[j] = players[j+1];
            }
            return true;
        }
    }
    return false;
}

void Matchmaking::sortByScoreInsertion() {
    int i, j;
    Player current;
    for(int i = 1; i < size; i++) {
        current = players[i];
        j = i - 1;

        while(j >= 0 && current.getScore() <= players[j].getScore()) {
            if(current.getScore() == players[j].getScore()) {
                if(current.getTimestamp() > players[j].getTimestamp()) {
                    break;
                }
            }
            players[j+1] = players[j];
            j = j - 1;
        }
        players[j+1] = current;
    }
}

void Matchmaking::merge(int left, int mid, int right) {
    Player* temp = new Player[right - left + 1];

    int i = left;
    int j = mid + 1;
    int k = 0;

    while(i <= mid && j <= right) {
        if(players[i].getScore() == players[j].getScore()) {
            if(players[i].getTimestamp() <= players[j].getTimestamp()) {
                temp[k] = players[i];
                k++;
                i++; 
            }
            else {
                temp[k] = players[j];
                k++;
                j++;
            }
        }
        else if(players[i].getScore() < players[j].getScore()) {
            temp[k] = players[i];
            i++;
            k++;
        }
        else if(players[i].getScore() > players[j].getScore()) {
            temp[k] = players[j];
            j++;
            k++;
        }
    }

    while(i <= mid) {
        temp[k] = players[i];
        k++;
        i++;
    }

    while(j <= right) {
        temp[k] = players[j];
        k++;
        j++;
    }

    for(int l = 0; l < right - left + 1; l++) {
        players[left + l] = temp[l];
    }

    delete[] temp;
}

void Matchmaking::mergeSort(int left, int right) {
    if(left >= right) 
        return;
    int mid = (right + left) / 2;
    mergeSort(left, mid);
    mergeSort(mid + 1, right);
    merge(left, mid, right);
}

void Matchmaking::sortByScoreMerge() {
    mergeSort(0, size - 1);
}

Player* Matchmaking::getWaitingPlayers(int* n) {
    if(size == 0) {
        *n = 0;
        return nullptr;
    }
    *n = size;
    Player* temp = new Player[*n];
    for(int i = 0; i < *n; i++) {
        temp[i] = players[i];
    }
    return temp;
}

void Matchmaking::printWaitingPlayers() {
    cout << "Waiting players:" << endl;
    for(int i = 0; i < size; i++) {
        cout << "[ " << players[i].getId() << " | " << players[i].getName() << " | " << players[i].getScore() << " | " << players[i].getTimestamp() << " ]" << endl;
    }
}