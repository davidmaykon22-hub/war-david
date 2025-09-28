// Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

// --- Constantes Globais ---
#define MAX_TERRITORIOS 5
#define MAX_NOME 30
#define MAX_COR 10
#define NUM_MISSOES 2

// --- Estruturas ---
typedef struct {
    char nome[MAX_NOME];   // Nome do território
    char cor[MAX_COR];     // Cor do exército
    int tropas;            // Número de tropas
} Territorio;

// --- Protótipos de Funções ---
Territorio* alocarMapa(int qtd);
void inicializarTerritorios(Territorio *mapa, int qtd);
void exibirMapa(const Territorio *mapa, int qtd);
void liberarMemoria(Territorio *mapa);

void exibirMenuPrincipal();
void exibirMissao(int idMissao);
int sortearMissao();
int verificarVitoria(const Territorio *mapa, int qtd, int idMissao, const char *corJogador);

void faseDeAtaque(Territorio *mapa, int qtd, const char *corJogador);
void simularAtaque(Territorio *origem, Territorio *destino);

void limparBufferEntrada();

// Função Principal
// ============================================================================
int main() {
    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL));

    // 1. Configuração Inicial
    Territorio *mapa = alocarMapa(MAX_TERRITORIOS);
    if (mapa == NULL) {
        printf("Erro ao alocar memória para o mapa!\n");
        return 1;
    }

    inicializarTerritorios(mapa, MAX_TERRITORIOS);

    char corJogador[MAX_COR];
    printf("Digite a cor do seu exército: ");
    scanf(" %[^\n]", corJogador);

    int missao = sortearMissao();
    printf("\nSua missão secreta:\n");
    exibirMissao(missao);

    // 2. Loop 
    int opcao;
    int venceu = 0;
    do {
        printf("\n===== MENU PRINCIPAL =====\n");
        exibirMapa(mapa, MAX_TERRITORIOS);
        exibirMenuPrincipal();

        scanf("%d", &opcao);
        limparBufferEntrada();

        switch (opcao) {
            case 1:
                faseDeAtaque(mapa, MAX_TERRITORIOS, corJogador);
                break;
            case 2:
                exibirMissao(missao);
                break;
            case 3:
                venceu = verificarVitoria(mapa, MAX_TERRITORIOS, missao, corJogador);
                if (venceu)
                    printf("\n🎉 PARABÉNS! Você cumpriu sua missão!\n");
                else
                    printf("\nAinda não cumpriu a missão. Continue jogando!\n");
                break;
            case 0:
                printf("\nSaindo do jogo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }

    } while (opcao != 0 && !venceu);

    // 3. Limpeza
    liberarMemoria(mapa);
    return 0;
}

// Implementação das Funções
// ============================================================================

Territorio* alocarMapa(int qtd) {
    return (Territorio*) calloc(qtd, sizeof(Territorio));
}

void inicializarTerritorios(Territorio *mapa, int qtd) {
    printf("\nCadastro de Territórios\n\n");
    for (int i = 0; i < qtd; i++) {
        printf("Território %d:\n", i + 1);

        printf("Nome do território: ");
        scanf(" %[^\n]", mapa[i].nome);

        printf("Cor do exército: ");
        scanf(" %[^\n]", mapa[i].cor);

        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);

        printf("\n");
    }
}

void exibirMapa(const Territorio *mapa, int qtd) {
    for (int i = 0; i < qtd; i++) {
        printf("Território %d:\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor do Exército: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
        printf("-----------------------------\n");
    }
}

void liberarMemoria(Territorio *mapa) {
    free(mapa);
}

void exibirMenuPrincipal() {
    printf("\n1 - Atacar\n");
    printf("2 - Ver Missão\n");
    printf("3 - Verificar Vitória\n");
    printf("0 - Sair\n");
    printf("Escolha: ");
}

void exibirMissao(int idMissao) {
    printf("===== MISSÃO =====\n");
    switch (idMissao) {
        case 0:
            printf("Conquistar pelo menos 2 territórios inimigos.\n");
            break;
        case 1:
            printf("Destruir todos os territórios de uma cor inimiga específica.\n");
            break;
        default:
            printf("Missão inválida.\n");
    }
    printf("==================\n");
}

int sortearMissao() {
    return rand() % NUM_MISSOES;
}

int verificarVitoria(const Territorio *mapa, int qtd, int idMissao, const char *corJogador) {
    if (idMissao == 0) {
        // Missão: conquistar pelo menos 2 territórios
        int conquistados = 0;
        for (int i = 0; i < qtd; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0) {
                conquistados++;
            }
        }
        return (conquistados >= 2);
    } else if (idMissao == 1) {
        // Missão: destruir uma cor inimiga
        char corInimiga[MAX_COR] = "Vermelho"; // exemplo fixo
        for (int i = 0; i < qtd; i++) {
            if (strcmp(mapa[i].cor, corInimiga) == 0)
                return 0; // ainda existe território inimigo
        }
        return 1;
    }
    return 0;
}

void faseDeAtaque(Territorio *mapa, int qtd, const char *corJogador) {
    char origemNome[MAX_NOME], destinoNome[MAX_NOME];
    printf("\n=== FASE DE ATAQUE ===\n");
    printf("Informe o território de origem (seu): ");
    scanf(" %[^\n]", origemNome);
    printf("Informe o território de destino (inimigo): ");
    scanf(" %[^\n]", destinoNome);

    Territorio *origem = NULL;
    Territorio *destino = NULL;

    for (int i = 0; i < qtd; i++) {
        if (strcmp(mapa[i].nome, origemNome) == 0 && strcmp(mapa[i].cor, corJogador) == 0)
            origem = &mapa[i];
        if (strcmp(mapa[i].nome, destinoNome) == 0 && strcmp(mapa[i].cor, corJogador) != 0)
            destino = &mapa[i];
    }

    if (origem == NULL || destino == NULL) {
        printf("Territórios inválidos!\n");
        return;
    }

    if (origem->tropas < 2) {
        printf("Você precisa de pelo menos 2 tropas para atacar!\n");
        return;
    }

    simularAtaque(origem, destino);
}

void simularAtaque(Territorio *origem, Territorio *destino) {
    int dadoAtaque = rand() % 6 + 1;
    int dadoDefesa = rand() % 6 + 1;

    printf("\nAtaque de %s (%d tropas) contra %s (%d tropas)\n",
           origem->nome, origem->tropas, destino->nome, destino->tropas);
    printf("Dado do ataque: %d | Dado da defesa: %d\n", dadoAtaque, dadoDefesa);

    if (dadoAtaque > dadoDefesa) {
        destino->tropas--;
        printf("Defensor perdeu 1 tropa!\n");
        if (destino->tropas <= 0) {
            strcpy(destino->cor, origem->cor);
            destino->tropas = 1;
            origem->tropas--;
            printf("Território %s conquistado!\n", destino->nome);
        }
    } else {
        origem->tropas--;
        printf("Atacante perdeu 1 tropa!\n");
    }
}

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}