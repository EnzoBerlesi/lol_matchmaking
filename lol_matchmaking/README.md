# LoL Matchmaker — C++

Sistema de matchmaking inspirado no League of Legends, rodando 100% no console (CMD).

## Pré-requisitos

- **Windows** com **MinGW-w64** instalado (g++ ≥ 7, suporte a C++17)
  - Download: https://www.mingw-w64.org/  
  - Ou instale via **MSYS2**: `pacman -S mingw-w64-x86_64-gcc`
- `make` disponível no PATH (vem com MSYS2/MinGW)

## Como compilar e executar

```cmd
cd lol_matchmaking
make
matchmaker.exe
```

Sem `make`, compile manualmente:

```cmd
g++ -std=c++17 -Wall -Iinclude src\main.cpp src\Player.cpp src\PlayerList.cpp src\MatchQueue.cpp src\MatchStack.cpp src\Sorter.cpp src\Matchmaker.cpp src\Reports.cpp src\Menu.cpp -o matchmaker.exe
matchmaker.exe
```

## Estrutura do projeto

```
lol_matchmaking/
├── include/          # Cabeçalhos (.h)
│   ├── Player.h          – struct Player, enum Role
│   ├── PlayerList.h      – Lista encadeada (banco de dados)
│   ├── MatchQueue.h      – Fila FIFO de matchmaking
│   ├── MatchStack.h      – Pilha LIFO de partidas pendentes
│   ├── Sorter.h          – 4 algoritmos de ordenação
│   ├── Matchmaker.h      – Motor de montagem e resolução
│   ├── Reports.h         – Relatórios de console
│   └── Menu.h            – Interface e loop principal
├── src/              # Implementações (.cpp)
│   ├── main.cpp
│   ├── Player.cpp
│   ├── PlayerList.cpp
│   ├── MatchQueue.cpp
│   ├── MatchStack.cpp
│   ├── Sorter.cpp
│   ├── Matchmaker.cpp
│   ├── Reports.cpp
│   └── Menu.cpp
├── Makefile
└── README.md
```

## Funcionalidades do menu

| Opção | Descrição | Algoritmo |
|-------|-----------|-----------|
| 1 | Cadastrar jogador (Nome, role Primária e Secundária) | — |
| 2 | Inserir jogador na fila | Fila FIFO |
| 3 | Visualizar fila ativa | — |
| 4 | Formar partida (5 jogadores, roles balanceadas) | Quick Sort + Insertion Sort |
| 5 | Resolver partida (vitória/derrota, atualiza MMR e WR) | Pilha LIFO |
| 6 | Buscar / editar estatísticas de jogador | Lista Encadeada |
| 7 | Ranking de winrate por posição | Merge Sort |
| 8 | Popularidade de roles primárias | Bubble Sort |

## Regras de negócio

- MMR inicial: **1000** | Vitória: **+25** | Derrota: **−25** (mínimo 0)
- Winrate calculado dinamicamente: `wins / totalGames * 100`
- Montagem de time: ordena candidatos por MMR → tenta role primária → depois secundária
- Lobby exibe jogadores ordenados: Top → Jungle → Mid → ADC → Support
