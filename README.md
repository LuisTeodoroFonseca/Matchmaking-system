# Sistema de Matchmaking para Jogos Online

## Descrição do Projeto

Este projeto implementa um sistema simples de matchmaking para jogos online em C++, utilizando classes, modularização e algoritmos de ordenação implementados manualmente.

O sistema é responsável por:

- armazenar jogadores em uma fila de espera;
- ordenar jogadores por score;
- desempatar utilizando timestamp;
- remover jogadores da fila;
- recuperar jogadores armazenados;
- formar grupos válidos de jogadores com níveis de habilidade próximos.

---

## Estrutura dos Arquivos

```text
main.cpp
Matchmaking.hpp
Matchmaking.cpp
Player.hpp
Player.cpp
README.md
Relatorio.pdf
```

### Descrição dos arquivos

- `main.cpp`: arquivo principal contendo testes das funcionalidades;
- `Player.hpp`: declaração da classe `Player`;
- `Player.cpp`: implementação da classe `Player`;
- `Matchmaking.hpp`: declaração da classe `Matchmaking`;
- `Matchmaking.cpp`: implementação da classe `Matchmaking`;
- `README.md`: instruções do projeto;
- `Relatorio.pdf`: relatório técnico e análise do sistema.

---

## Compilação

Compile o projeto utilizando:

```bash
g++ main.cpp Matchmaking.cpp Player.cpp -o matchmaking
```

---

## Execução

Após compilar, execute:

```bash
./matchmaking
```

---

## Funcionalidades Implementadas

O sistema implementa:

- inserção de jogadores;
- remoção de jogadores;
- ordenação utilizando insertion sort;
- ordenação utilizando merge sort;
- desempate por timestamp;
- recuperação dos jogadores armazenados;
- impressão da fila de espera;
- formação de grupos válidos.

---

## Ordenação dos Jogadores

Os jogadores são ordenados seguindo os critérios:

1. menor score;
2. em caso de empate, menor timestamp.

Exemplo:

```text
[2 | Bruno | 900  | 2]
[4 | Diego | 900  | 4]
[3 | Carla | 1000 | 1]
[1 | Ana   | 1000 | 5]
```

---

## Formação de Grupo

O sistema forma grupos consecutivos após a ordenação.

Um grupo é válido quando:

```text
maior_score - menor_score <= delta
```

O primeiro grupo válido encontrado é retornado e removido da fila.

---

## Testes

O arquivo `main.cpp` contém testes demonstrando:

- inserção;
- remoção;
- ordenação com insertion sort;
- ordenação com merge sort;
- desempate por timestamp;
- formação bem sucedida de grupo;
- tentativa sem sucesso de formação de grupo;
- recuperação de dados via getWaitingPlayers;
- exibição do estado do sistema;

---

