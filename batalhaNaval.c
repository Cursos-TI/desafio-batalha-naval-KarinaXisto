#include <stdio.h>

// Tamanho do tabuleiro
#define TAMANHO_TABULEIRO 10
// Valor para representar água
#define AGUA 0
// Valor para representar uma parte do navio
#define NAVIO 3
// Tamanho dos navios (fixo para este nível)
#define TAMANHO_NAVIO 3

// Função para exibir o tabuleiro
// Recebe a matriz do tabuleiro como parâmetro
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("--- TABULEIRO ---\n");
    // Loop externo para iterar sobre as linhas do tabuleiro
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        // Loop interno para iterar sobre as colunas do tabuleiro
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]); // Imprime o valor da posição (0 para água, 3 para navio)
        }
        printf("\n"); // Quebra de linha após cada linha para formatar o tabuleiro
    }
    printf("-----------------\n");
}

// Função para verificar se uma posição está dentro dos limites do tabuleiro
// Retorna 1 se estiver dentro, 0 caso contrário
int estaDentroDoLimite(int linha, int coluna) {
    return (linha >= 0 && linha < TAMANHO_TABULEIRO &&
            coluna >= 0 && coluna < TAMANHO_TABULEIRO);
}

// Função para posicionar um navio (horizontal, vertical ou diagonal)
// Retorna 1 se o posicionamento for bem-sucedido, 0 caso contrário (fora dos limites ou sobreposição)
// Parametros:
// - tabuleiro: matriz do tabuleiro
// - linhaInicial: linha de início do navio
// - colunaInicial: coluna de início do navio
// - tipo: 'H' para horizontal, 'V' para vertical, 'D1' para diagonal principal (linha e coluna aumentam),
//         'D2' para diagonal secundária (linha aumenta, coluna diminui)
int posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linhaInicial, int colunaInicial, char tipo) {
    int i, j; // Variáveis de loop para linha e coluna
    
    // Arrays para armazenar as posições que o navio ocuparia
    int linhasParaVerificar[TAMANHO_NAVIO];
    int colunasParaVerificar[TAMANHO_NAVIO];

    // Preenche as posições que o navio tentará ocupar com base no seu tipo
    if (tipo == 'H') { // Navio Horizontal
        // Verifica se o navio cabe no tabuleiro na horizontal
        if (colunaInicial + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
            printf("Erro: Navio horizontal excede os limites do tabuleiro.\n");
            return 0;
        }
        for (int k = 0; k < TAMANHO_NAVIO; k++) {
            linhasParaVerificar[k] = linhaInicial;
            colunasParaVerificar[k] = colunaInicial + k;
        }
    } else if (tipo == 'V') { // Navio Vertical
        // Verifica se o navio cabe no tabuleiro na vertical
        if (linhaInicial + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
            printf("Erro: Navio vertical excede os limites do tabuleiro.\n");
            return 0;
        }
        for (int k = 0; k < TAMANHO_NAVIO; k++) {
            linhasParaVerificar[k] = linhaInicial + k;
            colunasParaVerificar[k] = colunaInicial;
        }
    } else if (tipo == 'D1') { // Navio Diagonal Principal (linha e coluna aumentam)
        // Verifica se o navio cabe no tabuleiro na diagonal
        if (linhaInicial + TAMANHO_NAVIO > TAMANHO_TABULEIRO || colunaInicial + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
            printf("Erro: Navio diagonal (D1) excede os limites do tabuleiro.\n");
            return 0;
        }
        for (int k = 0; k < TAMANHO_NAVIO; k++) {
            linhasParaVerificar[k] = linhaInicial + k;
            colunasParaVerificar[k] = colunaInicial + k;
        }
    } else if (tipo == 'D2') { // Navio Diagonal Secundária (linha aumenta, coluna diminui)
        // Validação corrigida para navio diagonal D2
        if (linhaInicial + TAMANHO_NAVIO > TAMANHO_TABULEIRO || colunaInicial - (TAMANHO_NAVIO - 1) < 0) { 
            printf("Erro: Navio diagonal (D2) excede os limites do tabuleiro.\n");
            return 0;
        }
        for (int k = 0; k < TAMANHO_NAVIO; k++) {
            linhasParaVerificar[k] = linhaInicial + k;
            colunasParaVerificar[k] = colunaInicial - k;
        }
    } else {
        printf("Erro: Tipo de navio inválido. Use 'H', 'V', 'D1' ou 'D2'.\n");
        return 0;
    }

    // Valida se as posições estão dentro dos limites e verifica sobreposição antes de posicionar
    for (int k = 0; k < TAMANHO_NAVIO; k++) {
        i = linhasParaVerificar[k];
        j = colunasParaVerificar[k];

        if (!estaDentroDoLimite(i, j)) {
            printf("Erro: Parte do navio em (%d, %d) está fora dos limites do tabuleiro.\n", i, j);
            return 0;
        }
        if (tabuleiro[i][j] == NAVIO) {
            printf("Erro: Sobreposição de navios detectada em (%d, %d).\n", i, j);
            return 0;
        }
    }

    // Se todas as validações passaram, posicione o navio
    for (int k = 0; k < TAMANHO_NAVIO; k++) {
        i = linhasParaVerificar[k];
        j = colunasParaVerificar[k];
        tabuleiro[i][j] = NAVIO;
        printf("Navio posicionado em: (%d, %d)\n", i, j);
    }
    return 1; // Posicionamento bem-sucedido
}

int main() {
    // Declaração e inicialização do tabuleiro com água (0)
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }

    printf("Iniciando posicionamento dos navios...\n\n");

    // Navio 1: Horizontal
    printf("Posicionando Navio 1 (Horizontal):\n");
    if (!posicionarNavio(tabuleiro, 1, 1, 'H')) { // Linha 1, Coluna 1, Horizontal
        printf("Falha ao posicionar Navio 1.\n");
    }
    printf("\n");

    // Navio 2: Vertical
    printf("Posicionando Navio 2 (Vertical):\n");
    if (!posicionarNavio(tabuleiro, 4, 8, 'V')) { // Linha 4, Coluna 8, Vertical
        printf("Falha ao posicionar Navio 2.\n");
    }
    printf("\n");

    // Navio 3: Diagonal Principal (linha e coluna aumentam)
    printf("Posicionando Navio 3 (Diagonal Principal):\n");
    if (!posicionarNavio(tabuleiro, 0, 0, 'D1')) { // Linha 0, Coluna 0, Diagonal 1
        printf("Falha ao posicionar Navio 3.\n");
    }
    printf("\n");

    // Navio 4: Diagonal Secundária (linha aumenta, coluna diminui)
    printf("Posicionando Navio 4 (Diagonal Secundária):\n");
    // Coordenadas escolhidas para não haver sobreposição com os navios anteriores
    if (!posicionarNavio(tabuleiro, 2, 7, 'D2')) { // Linha 2, Coluna 7, Diagonal 2
        printf("Falha ao posicionar Navio 4.\n");
    }
    printf("\n");

    // Exibir o tabuleiro final
    exibirTabuleiro(tabuleiro);

    return 0;
}