#include <stdio.h>
#include <stdlib.h> // Para malloc, free, realloc
#include <string.h> // Para strcpy

// --- Definição da Estrutura Aluno ---
typedef struct {
    char nome[50];
    float *mediasDisciplinas; // Ponteiro para um array dinâmico de médias por disciplina
    int numDisciplinas;
    float mediaGeralFinal;    // Média geral final do aluno, calculada a partir das médias das disciplinas
} Aluno;

// --- Protótipos das Funções ---
void cadastrarAluno(Aluno **alunos, int *numAlunos, int maxDisciplinas);
void calcularMediaGeral(Aluno *aluno);
void listarAlunos(Aluno *alunos, int numAlunos);
void selectionSort(Aluno *alunos, int numAlunos);
void liberarMemoria(Aluno *alunos, int numAlunos);

// --- Função Principal ---
int main() {
    Aluno *alunos = NULL; // Ponteiro para o vetor dinâmico de alunos
    int numAlunos = 0;    // Quantidade atual de alunos cadastrados
    int maxDisciplinas = 5; // Limite de disciplinas

    int opcao;

    do {
        printf("\n--- Gerenciador de Medias de Alunos ---\n");
        printf("1. Cadastrar Aluno\n");
        printf("2. Listar Alunos\n");
        printf("3. Ordenar Alunos por Media Geral (Selection Sort)\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarAluno(&alunos, &numAlunos, maxDisciplinas);
                break;
            case 2:
                listarAlunos(alunos, numAlunos);
                break;
            case 3:
                if (numAlunos > 0) {
                    selectionSort(alunos, numAlunos);
                    printf("\nAlunos ordenados com sucesso pela media geral!\n");
                } else {
                    printf("\nNenhum aluno cadastrado para ordenar.\n");
                }
                break;
            case 0:
                printf("\nSaindo do programa. Ate mais!\n");
                break;
            default:
                printf("\nOpcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);

    // Liberar toda a memória alocada antes de sair
    liberarMemoria(alunos, numAlunos);

    return 0;
}

// --- Funções Auxiliares ---

// Função para cadastrar um novo aluno
void cadastrarAluno(Aluno **alunos, int *numAlunos, int maxDisciplinas) {
    // Aumenta o tamanho do vetor de alunos em 1
    *alunos = (Aluno *)realloc(*alunos, (*numAlunos + 1) * sizeof(Aluno));
    if (*alunos == NULL) {
        printf("Erro ao alocar memoria para o aluno.\n");
        exit(1); // Sai do programa em caso de erro fatal de memória
    }

    // Pega o endereço do novo aluno no vetor
    Aluno *novoAluno = &(*alunos)[*numAlunos];

    printf("\n--- Cadastro de Novo Aluno ---\n");
    printf("Nome do aluno: ");
    scanf(" %[^\n]%*c", novoAluno->nome); // Lê a linha inteira, incluindo espaços

    printf("Quantas disciplinas o aluno possui (max %d)? ", maxDisciplinas);
    scanf("%d", &novoAluno->numDisciplinas);

    // Valida o número de disciplinas
    while (novoAluno->numDisciplinas <= 0 || novoAluno->numDisciplinas > maxDisciplinas) {
        printf("Numero de disciplinas invalido. Digite um valor entre 1 e %d: ", maxDisciplinas);
        scanf("%d", &novoAluno->numDisciplinas);
    }

    // Aloca memória para as médias das disciplinas do aluno
    novoAluno->mediasDisciplinas = (float *)malloc(novoAluno->numDisciplinas * sizeof(float));
    if (novoAluno->mediasDisciplinas == NULL) {
        printf("Erro ao alocar memoria para as medias das disciplinas.\n");
        exit(1);
    }

    // Pede as médias das disciplinas
    for (int i = 0; i < novoAluno->numDisciplinas; i++) {
        printf("Media da disciplina %d: ", i + 1);
        scanf("%f", &novoAluno->mediasDisciplinas[i]);
    }

    // Calcula a média geral final do aluno
    calcularMediaGeral(novoAluno);

    (*numAlunos)++; // Incrementa o contador de alunos
    printf("Aluno cadastrado com sucesso!\n");
}

// Função para calcular a média geral de um aluno (a partir das médias das disciplinas)
void calcularMediaGeral(Aluno *aluno) {
    float soma = 0.0;
    for (int i = 0; i < aluno->numDisciplinas; i++) {
        soma += aluno->mediasDisciplinas[i];
    }
    aluno->mediaGeralFinal = soma / aluno->numDisciplinas;
}

// Função para listar todos os alunos cadastrados
void listarAlunos(Aluno *alunos, int numAlunos) {
    if (numAlunos == 0) {
        printf("\nNenhum aluno cadastrado.\n");
        return;
    }

    printf("\n--- Lista de Alunos ---\n");
    for (int i = 0; i < numAlunos; i++) {
        printf("Nome: %s\n", alunos[i].nome);
        printf("Medias por Disciplina: ");
        for (int j = 0; j < alunos[i].numDisciplinas; j++) {
            printf("%.2f ", alunos[i].mediasDisciplinas[j]);
        }
        printf("\nMedia Geral Final: %.2f\n", alunos[i].mediaGeralFinal);
        printf("--------------------\n");
    }
}

// Função de ordenação Selection Sort
void selectionSort(Aluno *alunos, int numAlunos) {
    int i, j, min_idx;
    Aluno temp; // Para a troca de alunos

    // Percorre todo o array
    for (i = 0; i < numAlunos - 1; i++) {
        // Encontra o índice do menor elemento restante
        min_idx = i;
        for (j = i + 1; j < numAlunos; j++) {
            if (alunos[j].mediaGeralFinal < alunos[min_idx].mediaGeralFinal) {
                min_idx = j;
            }
        }

        // Troca o menor elemento encontrado com o primeiro elemento não ordenado
        // Importante: fazemos uma cópia da estrutura inteira, não apenas ponteiros
        temp = alunos[min_idx];
        alunos[min_idx] = alunos[i];
        alunos[i] = temp;
    }
}

// Função para liberar a memória alocada dinamicamente
void liberarMemoria(Aluno *alunos, int numAlunos) {
    if (alunos == NULL) {
        return; // Nada para liberar
    }

    // Primeiro, libera a memória de cada array de médias de disciplinas
    for (int i = 0; i < numAlunos; i++) {
        free(alunos[i].mediasDisciplinas);
        alunos[i].mediasDisciplinas = NULL; // Boa prática: seta o ponteiro para NULL após liberar
    }

    // Depois, libera o vetor de alunos
    free(alunos);
    alunos = NULL; // Boa prática: seta o ponteiro para NULL após liberar
    printf("\nMemoria liberada com sucesso.\n");
}

