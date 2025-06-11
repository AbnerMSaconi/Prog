#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NOME 50
#define MAX_NOTAS 5

typedef struct {
    int RA; // max 6 digitos
    char nome[MAX_NOME];
    int qtdeNotas;
    float notas[MAX_NOTAS];
    float media;
} Aluno;

Aluno* alunos = NULL; // vetor dinâmico de alunos
int totalAlunos = 0;
int capacidade = 0;

// Função para ler inteiro com validação (intervalo)
int lerInt(const char* mensagem, int min, int max) {
    char buffer[100];
    int valor;
    while (1) {
        printf("%s", mensagem);
        if (!fgets(buffer, sizeof(buffer), stdin)) {
            printf("Erro na leitura.\n");
            continue;
        }
        // Verifica se só tem dígitos e '\n'
        int valido = 1;
        for (int i = 0; buffer[i] != '\0' && buffer[i] != '\n'; i++) {
            if (!isdigit(buffer[i])) {
                valido = 0;
                break;
            }
        }
        if (!valido) {
            printf("Entrada invalida. Digite apenas numeros.\n");
            continue;
        }
        valor = atoi(buffer);
        if (valor < min || valor > max) {
            printf("Valor fora do intervalo [%d - %d].\n", min, max);
            continue;
        }
        return valor;
    }
}

// Função para ler float entre 0 e 10 (nota)
float lerNota(const char* mensagem) {
    char buffer[100];
    float valor;
    while (1) {
        printf("%s", mensagem);
        if (!fgets(buffer, sizeof(buffer), stdin)) {
            printf("Erro na leitura.\n");
            continue;
        }
        // Verifica caracteres válidos para float
        int ponto = 0, valido = 1;
        for (int i = 0; buffer[i] != '\0' && buffer[i] != '\n'; i++) {
            if (!(isdigit(buffer[i]) || (buffer[i] == '.' && ponto == 0))) {
                valido = 0;
                break;
            }
            if (buffer[i] == '.') ponto = 1;
        }
        if (!valido) {
            printf("Entrada invalida. Digite apenas numeros validos.\n");
            continue;
        }
        valor = atof(buffer);
        if (valor < 0 || valor > 10) {
            printf("Nota deve estar entre 0 e 10.\n");
            continue;
        }
        return valor;
    }
}

// Função para verificar se RA já existe
int RAexiste(int RA) {
    for (int i = 0; i < totalAlunos; i++) {
        if (alunos[i].RA == RA) return 1;
    }
    return 0;
}

// Expande o vetor dinâmico de alunos
void expandirVetor() {
    if (capacidade == 0) {
        capacidade = 2;
        alunos = malloc(capacidade * sizeof(Aluno));
    } else {
        capacidade *= 2;
        alunos = realloc(alunos, capacidade * sizeof(Aluno));
    }
    if (!alunos) {
        printf("Erro na alocacao de memoria.\n");
        exit(1);
    }
}

// Cadastrar aluno
void cadastrarAluno() {
    if (totalAlunos == capacidade) {
        expandirVetor();
    }

    int RA;
    while (1) {
        RA = lerInt("Digite o RA (max 6 digitos): ", 1, 999999);
        if (RAexiste(RA)) {
            printf("RA ja cadastrado! Digite outro.\n");
        } else {
            break;
        }
    }
    alunos[totalAlunos].RA = RA;

    printf("Digite o nome do aluno: ");
    fgets(alunos[totalAlunos].nome, MAX_NOME, stdin);
    alunos[totalAlunos].nome[strcspn(alunos[totalAlunos].nome, "\n")] = '\0'; // Remove \n

    int qtdeNotas = lerInt("Digite a quantidade de notas (1 a 5): ", 1, MAX_NOTAS);
    alunos[totalAlunos].qtdeNotas = qtdeNotas;

    float soma = 0.0f;
    for (int i = 0; i < qtdeNotas; i++) {
        char msg[50];
        snprintf(msg, sizeof(msg), "Digite a nota %d (0 a 10): ", i + 1);
        alunos[totalAlunos].notas[i] = lerNota(msg);
        soma += alunos[totalAlunos].notas[i];
    }
    alunos[totalAlunos].media = soma / qtdeNotas;

    totalAlunos++;
    printf("Aluno cadastrado com sucesso!\n");
}

// Listar alunos
void listarAlunos() {
    if (totalAlunos == 0) {
        printf("Nenhum aluno cadastrado.\n");
        return;
    }
    printf("\nLista de Alunos:\n");
    printf("|\tRA\t|\tNome\t|\tMedia\t|\n");
    printf("-------------------------------------------------\n");
    for (int i = 0; i < totalAlunos; i++) {
        printf("|\t%06d\t|\t%s\t|\t%.2f\t|\n", alunos[i].RA, alunos[i].nome, alunos[i].media);
        printf("-------------------------------------------------\n");
    }
}

// Selection Sort pelo campo media (decrescente)
void ordenarAlunos() {
    if (totalAlunos < 2) return;

    for (int i = 0; i < totalAlunos - 1; i++) {
        int max_idx = i;
        for (int j = i + 1; j < totalAlunos; j++) {
            if (alunos[j].media > alunos[max_idx].media) {
                max_idx = j;
            }
        }
        if (max_idx != i) {
            Aluno temp = alunos[i];
            alunos[i] = alunos[max_idx];
            alunos[max_idx] = temp;
        }
    }
    printf("Alunos ordenados pela media (decrescente).\n");
}

int main() {
    int opcao;
    do {
        printf("\nMenu:\n");
        printf("1. Cadastrar aluno\n");
        printf("2. Listar alunos\n");
        printf("3. Ordenar alunos pela media\n");
        printf("0. Sair\n");
        opcao = lerInt("Escolha uma opcao: ", 0, 3);

        switch (opcao) {
            case 1:
                cadastrarAluno();
                break;
            case 2:
                listarAlunos();
                break;
            case 3:
                ordenarAlunos();
                break;
            case 0:
                printf("Encerrando programa.\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 0);

    free(alunos);
    return 0;
}
