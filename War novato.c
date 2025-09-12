#include <stdio.h>
#include <string.h>

// Estrutura que representa um território com nome, cor do exército e número de tropas
typedef struct {
    char nome[30];     // Nome do território
    char cor[10];      // Cor do exército que está no controle
    int tropas;        // Quantidade de tropas presentes
} Territorio;

int main() {
    // Vetor dos 5 territórios
    Territorio territorios[5];

    // Entrada de dados
    printf(" Cadastro de Territórios\n\n");
    for (int i = 0; i < 5; i++) {
        printf("Território %d:\n", i + 1);

        // Nome do território
        printf("Nome do território: ");
        scanf(" %[^\n]", territorios[i].nome);  // Lê até a quebra de linha (com espaços)

        // Cor do exército
        printf("Cor do exército: ");
        scanf(" %[^\n]", territorios[i].cor);

        // Numero de tropas
        printf("Quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);

        printf("\n");
        }

    // Exibe as informações cadastradas
    printf("===== Informações dos Territórios =====\n\n");
    for (int i = 0; i < 5; i++) {
        printf("Território %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do Exército: %s\n", territorios[i].cor);
        printf("Tropas: %d\n", territorios[i].tropas);
        printf("-----------------------------\n");
    }

    return 0;
}
