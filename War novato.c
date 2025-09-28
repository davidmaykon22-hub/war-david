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