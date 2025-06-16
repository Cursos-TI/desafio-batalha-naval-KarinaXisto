#include <stdio.h>

#define BOARD_SIZE 10
#define SKILL_SIZE 7 // Tamanho das matrizes de habilidade (ex: 5x5 ou 7x7)

// Função para imprimir o tabuleiro
void printBoard(int board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == 0) {
                printf("~ "); // Água
            } else if (board[i][j] == 3) {
                printf("S "); // Navio
            } else if (board[i][j] == 5) {
                printf("X "); // Área afetada pela habilidade
            } else {
                printf("%d ", board[i][j]); // Para outros valores (se houver)
            }
        }
        printf("\n");
    }
}

// Função para criar a matriz de habilidade Cone
void createConeSkill(int skill[SKILL_SIZE][SKILL_SIZE]) {
    for (int i = 0; i < SKILL_SIZE; i++) {
        for (int j = 0; j < SKILL_SIZE; j++) {
            skill[i][j] = 0; // Inicializa com 0
        }
    }

    // Lógica para o cone (apontando para baixo)
    for (int i = 0; i < SKILL_SIZE; i++) {
        // Calcula o ponto de partida e fim para cada linha para formar o cone
        int start = SKILL_SIZE / 2 - i;
        int end = SKILL_SIZE / 2 + i;

        // Garante que a área não ultrapasse os limites da matriz
        if (start < 0) start = 0;
        if (end >= SKILL_SIZE) end = SKILL_SIZE - 1;

        for (int j = start; j <= end; j++) {
            if (j >= 0 && j < SKILL_SIZE) {
                skill[i][j] = 1;
            }
        }
    }
}

// Função para criar a matriz de habilidade Cruz
void createCrossSkill(int skill[SKILL_SIZE][SKILL_SIZE]) {
    for (int i = 0; i < SKILL_SIZE; i++) {
        for (int j = 0; j < SKILL_SIZE; j++) {
            skill[i][j] = 0; // Inicializa com 0
        }
    }

    int center = SKILL_SIZE / 2;

    // Linha central
    for (int j = 0; j < SKILL_SIZE; j++) {
        skill[center][j] = 1;
    }

    // Coluna central
    for (int i = 0; i < SKILL_SIZE; i++) {
        skill[i][center] = 1;
    }
}

// Função para criar a matriz de habilidade Octaedro (Losango)
void createOctahedronSkill(int skill[SKILL_SIZE][SKILL_SIZE]) {
    for (int i = 0; i < SKILL_SIZE; i++) {
        for (int j = 0; j < SKILL_SIZE; j++) {
            skill[i][j] = 0; // Inicializa com 0
        }
    }

    int center = SKILL_SIZE / 2;

    for (int i = 0; i < SKILL_SIZE; i++) {
        for (int j = 0; j < SKILL_SIZE; j++) {
            // A distância de Manhattan do centro define a forma de losango
            if (abs(i - center) + abs(j - center) <= center) {
                skill[i][j] = 1;
            }
        }
    }
}

// Função para sobrepor a habilidade no tabuleiro
void overlaySkill(int board[BOARD_SIZE][BOARD_SIZE], int skill[SKILL_SIZE][SKILL_SIZE], int originRow, int originCol) {
    int skillHalf = SKILL_SIZE / 2;

    for (int i = 0; i < SKILL_SIZE; i++) {
        for (int j = 0; j < SKILL_SIZE; j++) {
            if (skill[i][j] == 1) {
                // Calcula as coordenadas no tabuleiro
                int boardRow = originRow + (i - skillHalf);
                int boardCol = originCol + (j - skillHalf);

                // Verifica se as coordenadas estão dentro dos limites do tabuleiro
                if (boardRow >= 0 && boardRow < BOARD_SIZE && boardCol >= 0 && boardCol < BOARD_SIZE) {
                    // Marca a área afetada, a menos que já seja um navio (opcional, pode ser substituído)
                    if (board[boardRow][boardCol] != 3) {
                        board[boardRow][boardCol] = 5;
                    }
                }
            }
        }
    }
}

int main() {
    // Inicializa o tabuleiro com água (0)
    int board[BOARD_SIZE][BOARD_SIZE] = {0};

    // Posições dos navios (exemplo)
    board[2][2] = 3;
    board[2][3] = 3;
    board[2][4] = 3;
    board[5][7] = 3;
    board[6][7] = 3;
    board[7][7] = 3;

    // --- Habilidade Cone ---
    printf("Tabuleiro com Habilidade Cone (Origem: [1,4]):\n");
    int coneSkill[SKILL_SIZE][SKILL_SIZE];
    createConeSkill(coneSkill);
    overlaySkill(board, coneSkill, 1, 4); // Ponto de origem do cone
    printBoard(board);
    printf("\n");

    // Reinicia o tabuleiro para a próxima habilidade
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = 0;
        }
    }
    board[2][2] = 3;
    board[2][3] = 3;
    board[2][4] = 3;
    board[5][7] = 3;
    board[6][7] = 3;
    board[7][7] = 3;


    // --- Habilidade Cruz ---
    printf("Tabuleiro com Habilidade Cruz (Origem: [5,2]):\n");
    int crossSkill[SKILL_SIZE][SKILL_SIZE];
    createCrossSkill(crossSkill);
    overlaySkill(board, crossSkill, 5, 2); // Ponto de origem da cruz
    printBoard(board);
    printf("\n");

    // Reinicia o tabuleiro para a próxima habilidade
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = 0;
        }
    }
    board[2][2] = 3;
    board[2][3] = 3;
    board[2][4] = 3;
    board[5][7] = 3;
    board[6][7] = 3;
    board[7][7] = 3;


    // --- Habilidade Octaedro ---
    printf("Tabuleiro com Habilidade Octaedro (Origem: [4,6]):\n");
    int octahedronSkill[SKILL_SIZE][SKILL_SIZE];
    createOctahedronSkill(octahedronSkill);
    overlaySkill(board, octahedronSkill, 4, 6); // Ponto de origem do octaedro
    printBoard(board);
    printf("\n");

    return 0;
}