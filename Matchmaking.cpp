#include <iostream>
#include <random>
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
    if (size == MAX_PLAYERS)  //se o maximo de players foi atingido
        return false;
    players[size] = player; //insere ao final do array players
    size++;
    return true;
}

bool Matchmaking::removePlayer(int id) {
    for(int i = 0; i < size; i++) {
        if(players[i].getId() == id){
            size--;
            for(int j = i; j < size; j++) { //desloca os players seguintes uma posição para a esquerda
                players[j] = players[j+1];
            }
            return true;
        }
    }
    return false;
}

void Matchmaking::sortByScoreInsertion() { //ordena usando insertion sort
    int i, j;
    Player current;
    for(int i = 1; i < size; i++) {
        current = players[i];
        j = i - 1;
        //move jogadores com score menor (ou mesmo score e menor timestamp) uma posição à frente
        while(j >= 0 && current.getScore() <= players[j].getScore()) {
            //empate de score: ordena pelo menor timestamp
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
//combina dois arrays ordenados em um único array
void Matchmaking::merge(int left, int mid, int right) {
    Player* temp = new Player[right - left + 1];

    int i = left;
    int j = mid + 1;
    int k = 0;

    //intercala os dois subarrays enquanto ambos tiverem players
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
            temp[k] = players[i]; //direito tem score maior, vai primeiro
            i++;
            k++;
        }
        else if(players[i].getScore() > players[j].getScore()) {
            temp[k] = players[j]; //esquerdo tem score maior, vai primeiro
            j++;
            k++;
        }
    }
    //copia os elementos restantes do subarray esquerdo se houver
    while(i <= mid) {
        temp[k] = players[i];
        k++;
        i++;
    }
    //copia os elementos restantes do subarray direito se houver
    while(j <= right) {
        temp[k] = players[j];
        k++;
        j++;
    }
    //copia o array temporário de volta para players no intervalo correto
    for(int l = 0; l < right - left + 1; l++) {
        players[left + l] = temp[l];
    }

    delete[] temp;
}
//divide recursivamente cada array e ordena cada metade
void Matchmaking::mergeSort(int left, int right) {
    if(left >= right) //caso base
        return;
    int mid = (right + left) / 2;
    mergeSort(left, mid); //ordena metade esquerda
    mergeSort(mid + 1, right); //ordena metade direita
    merge(left, mid, right); //combina as duas metades ordenadas
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
//o array players deve estar ordenado antes de chamar a função
Player* Matchmaking::formGroup(int groupSize, int delta, int* n) {
    // Percorre janelas de tamanho groupSize procurando uma com diferença <= delta
    for (int i = 0; i <= size - groupSize; i++) {
        // Verifica se a diferença entre o maior e o menor score da janela é aceitável
        if (players[i + groupSize - 1].getScore() -
            players[i].getScore() <= delta) {
            // Aloca e copia os jogadores do grupo encontrado
            Player* playingGroup = new Player[groupSize];
            for (int j = 0; j < groupSize; j++) {
                playingGroup[j] = players[i + j];
            }
            // Remove os jogadores do grupo da fila de matchmaking
            for (int j = 0; j < groupSize; j++) {
                removePlayer(players[i].getId());
            }

            *n = groupSize;
            return playingGroup;
        }
    }

    *n = 0;
    return nullptr;
}

void Matchmaking::printWaitingPlayers() {
    cout << "Waiting players:" << endl;
    for(int i = 0; i < size; i++) {
        cout << "[ " << players[i].getId() << " | " << players[i].getName() << " | " << players[i].getScore() << " | " << players[i].getTimestamp() << " ]" << endl;
    }
}

void Matchmaking::shuffle() {

    random_device rd;
    mt19937 gen(rd());

    for (int i = size - 1; i > 0; i--) {

        uniform_int_distribution<> dist(0, i);

        int j = dist(gen);

        // troca players[i] com players[j]
        Player temp = players[i];
        players[i] = players[j];
        players[j] = temp;
    }
}