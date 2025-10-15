#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20

// Estrutura de dados principal
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
    int prioridade;
} Componente;

// Funções principais
void adicionarComponente(Componente mochila[], int *qtd);
void listarComponentes(Componente mochila[], int qtd);
void bubbleSortNome(Componente mochila[], int qtd, int *comparacoes);
void insertionSortTipo(Componente mochila[], int qtd, int *comparacoes);
void selectionSortPrioridade(Componente mochila[], int qtd, int *comparacoes);
int buscaBinariaPorNome(Componente mochila[], int qtd, char nomeBuscado[], int *comparacoes);
void organizarMochila(Componente mochila[], int qtd, int *ordenadoPorNome);

// Função principal
int main() {
    Componente mochila[MAX_COMPONENTES];
    int qtd = 0;
    int opcao;
    int ordenadoPorNome = 0;

    do {
        printf("\n==============================================================\n");
        printf("        PLANO DE FUGA - CODIGO DA ILHA (NIVEL MESTRE)\n");
        printf("==============================================================\n");
        printf("Itens na Mochila: %d/%d\n", qtd, MAX_COMPONENTES);
        printf("Status da Ordenacao por Nome: %s\n", ordenadoPorNome ? "ORDENADO" : "NAO ORDENADO");
        printf("--------------------------------------------------------------\n");
        printf("1. Adicionar Componente\n");
        printf("2. Descartar Componente\n");
        printf("3. Listar Componentes (Inventario)\n");
        printf("4. Organizar Mochila (Ordenar Componentes)\n");
        printf("5. Busca Binaria por Componente-Chave (por nome)\n");
        printf("0. ATIVAR TORRE DE FUGA (Sair)\n");
        printf("--------------------------------------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                adicionarComponente(mochila, &qtd);
                listarComponentes(mochila, qtd);
                break;

            case 2:
                if (qtd > 0) {
                    char nome[30];
                    printf("Digite o nome do componente a remover: ");
                    fgets(nome, 30, stdin);
                    nome[strcspn(nome, "\n")] = '\0';
                    int encontrado = 0;
                    for (int i = 0; i < qtd; i++) {
                        if (strcmp(mochila[i].nome, nome) == 0) {
                            for (int j = i; j < qtd - 1; j++) {
                                mochila[j] = mochila[j + 1];
                            }
                            qtd--;
                            encontrado = 1;
                            printf("Componente removido com sucesso!\n");
                            break;
                        }
                    }
                    if (!encontrado) printf("Componente nao encontrado!\n");
                } else {
                    printf("Mochila vazia!\n");
                }
                break;

            case 3:
                listarComponentes(mochila, qtd);
                break;

            case 4:
                organizarMochila(mochila, qtd, &ordenadoPorNome);
                break;

            case 5:
                if (!ordenadoPorNome) {
                    printf("\nAlerta! A busca binária requer que a mochila esteja ordenada por nome.\n");
                    printf("Use a opção 4 para ordenar a mochila primeiro.\n");
                } else {
                    char nomeBuscado[30];
                    int comparacoes = 0;
                    printf("Digite o nome do componente-chave: ");
                    fgets(nomeBuscado, 30, stdin);
                    nomeBuscado[strcspn(nomeBuscado, "\n")] = '\0';

                    int pos = buscaBinariaPorNome(mochila, qtd, nomeBuscado, &comparacoes);
                    if (pos != -1) {
                        printf("\nComponente encontrado!\n");
                        printf("----------------------------------------------\n");
                        printf("Nome                Tipo           Quantidade  Prioridade\n");
                        printf("---------------------------------------------------------\n");
                        printf("%-20s %-15s %-10d %d\n",
                               mochila[pos].nome, mochila[pos].tipo,
                               mochila[pos].quantidade, mochila[pos].prioridade);
                    } else {
                        printf("\nComponente nao encontrado!\n");
                    }
                    printf("Comparacoes realizadas: %d\n", comparacoes);
                }
                break;

            case 0:
                printf("\nAtivando Torre de Fuga... Boa sorte, sobrevivente!\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}

// Função para adicionar componente
void adicionarComponente(Componente mochila[], int *qtd) {
    if (*qtd >= MAX_COMPONENTES) {
        printf("Mochila cheia!\n");
        return;
    }

    printf("Digite o nome do componente: ");
    fgets(mochila[*qtd].nome, 30, stdin);
    mochila[*qtd].nome[strcspn(mochila[*qtd].nome, "\n")] = '\0';

    printf("Digite o tipo do componente: ");
    fgets(mochila[*qtd].tipo, 20, stdin);
    mochila[*qtd].tipo[strcspn(mochila[*qtd].tipo, "\n")] = '\0';

    printf("Digite a quantidade: ");
    scanf("%d", &mochila[*qtd].quantidade);
    getchar();

    printf("Digite a prioridade de montagem (1 a 5): ");
    scanf("%d", &mochila[*qtd].prioridade);
    getchar();

    (*qtd)++;
    printf("\nComponente adicionado com sucesso!\n");
}

// Listagem formatada dos componentes
void listarComponentes(Componente mochila[], int qtd) {
    if (qtd == 0) {
        printf("\nNenhum componente na mochila!\n");
        return;
    }

    printf("\n================= INVENTARIO DE COMPONENTES =================\n");
    printf("Nome                 Tipo            Quantidade  Prioridade\n");
    printf("-------------------------------------------------------------\n");

    for (int i = 0; i < qtd; i++) {
        printf("%-20s %-15s %-10d %d\n",
               mochila[i].nome, mochila[i].tipo,
               mochila[i].quantidade, mochila[i].prioridade);
    }
    printf("-------------------------------------------------------------\n");
}

// Métodos de ordenação
void bubbleSortNome(Componente mochila[], int qtd, int *comparacoes) {
    for (int i = 0; i < qtd - 1; i++) {
        for (int j = 0; j < qtd - i - 1; j++) {
            (*comparacoes)++;
            if (strcmp(mochila[j].nome, mochila[j + 1].nome) > 0) {
                Componente temp = mochila[j];
                mochila[j] = mochila[j + 1];
                mochila[j + 1] = temp;
            }
        }
    }
}

void insertionSortTipo(Componente mochila[], int qtd, int *comparacoes) {
    for (int i = 1; i < qtd; i++) {
        Componente chave = mochila[i];
        int j = i - 1;
        while (j >= 0 && strcmp(mochila[j].tipo, chave.tipo) > 0) {
            (*comparacoes)++;
            mochila[j + 1] = mochila[j];
            j--;
        }
        mochila[j + 1] = chave;
    }
}

void selectionSortPrioridade(Componente mochila[], int qtd, int *comparacoes) {
    for (int i = 0; i < qtd - 1; i++) {
        int min = i;
        for (int j = i + 1; j < qtd; j++) {
            (*comparacoes)++;
            if (mochila[j].prioridade < mochila[min].prioridade) {
                min = j;
            }
        }
        Componente temp = mochila[i];
        mochila[i] = mochila[min];
        mochila[min] = temp;
    }
}

// Busca binária por nome
int buscaBinariaPorNome(Componente mochila[], int qtd, char nomeBuscado[], int *comparacoes) {
    int inicio = 0, fim = qtd - 1;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        (*comparacoes)++;
        int cmp = strcmp(nomeBuscado, mochila[meio].nome);
        if (cmp == 0)
            return meio;
        else if (cmp < 0)
            fim = meio - 1;
        else
            inicio = meio + 1;
    }
    return -1;
}

// Menu de ordenação
void organizarMochila(Componente mochila[], int qtd, int *ordenadoPorNome) {
    int opcao, comparacoes = 0;
    clock_t inicio, fim;
    double tempo;

    printf("\nEscolha o metodo de ordenacao:\n");
    printf("1. Ordenação por Nome\n");
    printf("2. Ordenação por Tipo\n");
    printf("3. Ordenação por Prioridade\n");
    printf("0. Cancelar\n");
    printf("Opcao: ");
    scanf("%d", &opcao);
    getchar();

    if (opcao == 0) {
        printf("Operacao cancelada.\n");
        return;
    }

    inicio = clock();
    switch (opcao) {
        case 1:
            bubbleSortNome(mochila, qtd, &comparacoes);
            *ordenadoPorNome = 1;
            break;
        case 2:
            insertionSortTipo(mochila, qtd, &comparacoes);
            *ordenadoPorNome = 0;
            break;
        case 3:
            selectionSortPrioridade(mochila, qtd, &comparacoes);
            *ordenadoPorNome = 0;
            break;
        default:
            printf("Opcao invalida!\n");
            return;
    }
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("\nComponentes ordenados com sucesso!\n");
    listarComponentes(mochila, qtd);
    printf("Comparacoes realizadas: %d\n", comparacoes);
    printf("Tempo de execucao: %.5f segundos\n", tempo);
}
