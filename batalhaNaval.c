#include <stdio.h>

// Define o tamanho do tabuleiro
#define LINHAS 10
#define COLUNAS 10
// Define o tamanho fixo dos navios
#define TAMANHO_NAVIO 3
// Representa água no tabuleiro
#define AGUA 0
// Representa uma parte do navio no tabuleiro
#define NAVIO 3

// Função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[LINHAS][COLUNAS]) {
    printf("--- TABULEIRO ---\n");
    // Loop para iterar sobre as linhas do tabuleiro
    for (int i = 0; i < LINHAS; i++) {
        // Loop para iterar sobre as colunas do tabuleiro
        for (int j = 0; j < COLUNAS; j++) {
            printf("%d ", tabuleiro[i][j]); // Imprime o valor da posição (0 para água, 3 para navio)
        }
        printf("\n"); // Nova linha para a próxima linha do tabuleiro
    }
    printf("-----------------\n");
}

int main() {
    // Declaração e inicialização do tabuleiro com água (0)
    int tabuleiro[LINHAS][COLUNAS];
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }

    // --- Posicionamento do Navio Horizontal ---
    // Coordenadas iniciais do navio horizontal
    int linhaNavioH = 2;
    int colunaNavioH = 1;

    printf("Posicionando navio horizontal nas coordenadas:\n");
    // Loop para posicionar o navio horizontalmente
    for (int j = 0; j < TAMANHO_NAVIO; j++) {
        // Verifica se a posição está dentro dos limites do tabuleiro
        if (colunaNavioH + j < COLUNAS) {
            tabuleiro[linhaNavioH][colunaNavioH + j] = NAVIO; // Marca a posição com o valor do navio
            printf("(%d, %d)\n", linhaNavioH, colunaNavioH + j); // Exibe as coordenadas
        } else {
            printf("Atenção: Parte do navio horizontal fora dos limites do tabuleiro!\n");
            break; // Sai do loop se o navio exceder os limites
        }
    }

    // --- Posicionamento do Navio Vertical ---
    // Coordenadas iniciais do navio vertical
    int linhaNavioV = 4;
    int colunaNavioV = 6;

    printf("\nPosicionando navio vertical nas coordenadas:\n");
    // Loop para posicionar o navio verticalmente
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        // Verifica se a posição está dentro dos limites do tabuleiro
        if (linhaNavioV + i < LINHAS) {
            // Verifica se a posição já está ocupada por outro navio (sobreposição)
            if (tabuleiro[linhaNavioV + i][colunaNavioV] == NAVIO) {
                printf("Atenção: Sobreposição de navios detectada em (%d, %d)! Navio não pode ser posicionado aqui.\n", linhaNavioV + i, colunaNavioV);
                // Pode adicionar lógica para tentar um novo posicionamento ou simplesmente parar.
                break; // Neste exemplo, paramos o posicionamento do navio vertical.
            }
            tabuleiro[linhaNavioV + i][colunaNavioV] = NAVIO; // Marca a posição com o valor do navio
            printf("(%d, %d)\n", linhaNavioV + i, colunaNavioV); // Exibe as coordenadas
        } else {
            printf("Atenção: Parte do navio vertical fora dos limites do tabuleiro!\n");
            break; // Sai do loop se o navio exceder os limites
        }
    }

    // Exibe o tabuleiro final com os navios posicionados
    printf("\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}