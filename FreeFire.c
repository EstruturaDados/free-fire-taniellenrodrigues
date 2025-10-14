#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

// Definição da struct Item
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Protótipos das funções
void inserirItem(Item mochila[], int *totalItens);
void removerItem(Item mochila[], int *totalItens);
void listarItens(Item mochila[], int totalItens);

int main() {
    Item mochila[MAX_ITENS];  // Vetor que representa a mochila
    int totalItens = 0;       // Contador de itens na mochila
    int opcao;

    do {
        printf("\n=== Sistema de Inventario ===\n");
        printf("1. Inserir item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpar o buffer do teclado

        switch(opcao) {
            case 1:
                inserirItem(mochila, &totalItens);
                break;
            case 2:
                removerItem(mochila, &totalItens);
                break;
            case 3:
                listarItens(mochila, totalItens);
                break;
            case 0:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }

    } while(opcao != 0);

    return 0;
}

// Função para inserir um item na mochila
void inserirItem(Item mochila[], int *totalItens) {
    if (*totalItens >= MAX_ITENS) {
        printf("Mochila cheia! Nao e possivel adicionar mais itens.\n");
        return;
    }

    printf("Nome do item: ");
    scanf("%s", mochila[*totalItens].nome);

    printf("Tipo do item (arma, municao, cura): ");
    scanf("%s", mochila[*totalItens].tipo);

    printf("Quantidade: ");
    scanf("%d", &mochila[*totalItens].quantidade);

    (*totalItens)++;
    printf("Item adicionado com sucesso!\n");

    listarItens(mochila, *totalItens);
}

// Função para remover um item pelo nome
void removerItem(Item mochila[], int *totalItens) {
    if (*totalItens == 0) {
        printf("Mochila vazia! Nada para remover.\n");
        return;
    }

    char nome[30];
    printf("Digite o nome do item a remover: ");
    scanf("%s", nome);

    int encontrado = 0;
    for (int i = 0; i < *totalItens; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            // Deslocar itens para preencher o espaço
            for (int j = i; j < *totalItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*totalItens)--;
            encontrado = 1;
            printf("Item removido com sucesso!\n");
            break;
        }
    }
    if (!encontrado) {
        printf("Item nao encontrado.\n");
    }

    listarItens(mochila, *totalItens);
}

// Função para listar todos os itens da mochila
void listarItens(Item mochila[], int totalItens) {
    if (totalItens == 0) {
        printf("Mochila vazia.\n");
        return;
    }

    printf("\nItens na mochila:\n");
    for (int i = 0; i < totalItens; i++) {
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}
