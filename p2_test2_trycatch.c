#include <stdio.h>    // Para operações de entrada e saída (printf, scanf)
#include <stdlib.h>   // Para alocação de memória dinâmica (malloc, free, realloc, system)
#include <string.h>   // Para manipulação de strings (strcpy, strlen, strcspn)

// Define a estrutura (registro) para um Aluno
typedef struct {
    char nome[100];     // Nome do aluno (tamanho fixo para simplificar)
    double* notas;      // Ponteiro para um array dinâmico de notas
    int numDisciplinas;
    double mediaFinal;
} Aluno;

// Protótipos das Funções (Declarações)
void limparBufferEntrada();
void limparTela();
int cadastrarAluno(Aluno** alunos, int* numAlunos, int* capacidadeAlunos);
void listarAlunos(const Aluno* alunos, int numAlunos);
void selectionSort(Aluno* alunos, int numAlunos); // Nome da função de ordenação

int main() {
    // Alocação dinâmica inicial para o array de alunos (array de objetos Aluno)
    Aluno* alunos = NULL;
    int numAlunos = 0;
    int capacidadeAlunos = 0; // Capacidade inicial do array

    int escolha;
    do {
        limparTela(); // Limpa a tela antes de exibir o menu
        printf("\n--- Gerenciador de Notas de Alunos ---\n");
        printf("1. Cadastrar Aluno\n");
        printf("2. Listar Alunos\n");
        printf("3. Ordenar Alunos (Selection Sort)\n"); // Texto do menu atualizado
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &escolha) != 1) { // Verifica se a entrada foi bem-sucedida
            printf("Entrada invalida. Por favor, digite um numero.\n");
            limparBufferEntrada(); // Limpa o buffer em caso de entrada invalida
            // Pausa para o usuário ver a mensagem antes da tela ser limpa novamente
            printf("Pressione ENTER para continuar...");
            getchar(); // Espera por ENTER
            continue;
        }
        limparBufferEntrada(); // Limpa o buffer após scanf para números

        switch (escolha) {
            case 1:
                cadastrarAluno(&alunos, &numAlunos, &capacidadeAlunos);
                // Pausa para o usuário ver a mensagem antes da tela ser limpa novamente
                printf("\nPressione ENTER para continuar...");
                getchar(); // Espera por ENTER
                break;
            case 2:
                listarAlunos(alunos, numAlunos);
                printf("\nPressione ENTER para continuar...");
                getchar(); // Espera por ENTER
                break;
            case 3:
                selectionSort(alunos, numAlunos); // Chamada da função atualizada
                // Lista apenas se houver alunos para ver o resultado ordenado
                if (numAlunos > 1) {
                    listarAlunos(alunos, numAlunos);
                }
                printf("\nPressione ENTER para continuar...");
                getchar(); // Espera por ENTER
                break;
            case 0:
                printf("Saindo do programa. Ate mais!\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                printf("Pressione ENTER para continuar...");
                getchar(); // Espera por ENTER
                break;
        }
    } while (escolha != 0);

    // Libera a memória alocada para cada array de notas
    for (int i = 0; i < numAlunos; ++i) {
        free(alunos[i].notas);
        alunos[i].notas = NULL; // Boa prática para evitar ponteiros pendentes
    }
    // Libera a memória alocada para o array principal de alunos
    free(alunos);
    alunos = NULL; // Boa prática para evitar ponteiros pendentes

    return 0;
}

// Função para limpar o buffer de entrada
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para limpar a tela do terminal
void limparTela() {
#ifdef _WIN32
    system("cls"); // Para Windows
#else
    system("clear"); // Para sistemas Unix (Linux, macOS)
#endif
}

// Função para cadastrar um novo aluno
// Retorna 0 em caso de sucesso, -1 em caso de erro (ex: falha de alocação)
int cadastrarAluno(Aluno** alunos, int* numAlunos, int* capacidadeAlunos) {
    // Verifica se há espaço no array atual, se não, realoca com mais capacidade
    if (*numAlunos == *capacidadeAlunos) {
        // Aumenta a capacidade do array principal de alunos
        int novaCapacidade = (*capacidadeAlunos == 0) ? 1 : (*capacidadeAlunos) * 2;
        Aluno* novoVetor = (Aluno*)realloc(*alunos, novaCapacidade * sizeof(Aluno));

        if (novoVetor == NULL) {
            printf("Erro: Nao foi possivel realocar memoria para o array de alunos. Cadastro falhou.\n");
            return -1; // Indica falha na alocação
        }
        *alunos = novoVetor;     // Atualiza o ponteiro para o novo array
        *capacidadeAlunos = novaCapacidade; // Atualiza a capacidade
    }

    // Acessa o espaço para o novo aluno no array
    Aluno* novoAluno = &(*alunos)[*numAlunos];

    printf("\n--- Cadastrar Aluno ---\n");
    printf("Nome do aluno: ");
    fgets(novoAluno->nome, sizeof(novoAluno->nome), stdin);
    // Remove o '\n' que fgets pode adicionar no final
    novoAluno->nome[strcspn(novoAluno->nome, "\n")] = 0;

    int numDisciplinas;
    do {
        printf("Quantidade de disciplinas (limite: 1 a 5): ");
        if (scanf("%d", &numDisciplinas) != 1 || numDisciplinas < 1 || numDisciplinas > 5) {
            printf("Entrada invalida. Por favor, digite um numero entre 1 e 5.\n");
            limparBufferEntrada();
        } else {
            limparBufferEntrada(); // Limpa o buffer após scanf
            break;
        }
    } while (1);

    novoAluno->numDisciplinas = numDisciplinas;
    // Alocação dinâmica para as notas do aluno
    novoAluno->notas = (double*)malloc(numDisciplinas * sizeof(double));
    if (novoAluno->notas == NULL) {
        printf("Erro: Nao foi possivel alocar memoria para as notas do aluno. Cadastro falhou.\n");
        // Se a alocação de notas falhar, não podemos adicionar o aluno
        // e o espaço no array principal de alunos permanece vazio
        return -1; // Indica falha na alocação
    }

    double somaNotas = 0.0;
    for (int i = 0; i < numDisciplinas; ++i) {
        double nota;
        do {
            printf("Nota da disciplina %d (0 a 10): ", (i + 1));
            if (scanf("%lf", &nota) != 1 || nota < 0 || nota > 10) {
                printf("Nota invalida. Por favor, digite um valor entre 0 e 10.\n");
                limparBufferEntrada();
            } else {
                limparBufferEntrada(); // Limpa o buffer após scanf
                novoAluno->notas[i] = nota;
                break;
            }
        } while (1);
        somaNotas += novoAluno->notas[i];
    }

    novoAluno->mediaFinal = somaNotas / numDisciplinas;

    (*numAlunos)++; // Incrementa o contador de alunos
    printf("Aluno cadastrado com sucesso!\n");
    return 0; // Indica sucesso
}

// Função para listar todos os alunos com suas médias
void listarAlunos(const Aluno* alunos, int numAlunos) {
    if (numAlunos == 0) {
        printf("\nNenhum aluno cadastrado.\n");
        return;
    }

    printf("\n--- Lista de Alunos ---\n");
    printf("------------------------------------------------------------------------------------\n"); // Ajustado o tamanho da linha
    // Ajustado o alinhamento das colunas para Notas e Media Final e adicionado separadores
    printf("%-25s | %-40s | %s\n", "Nome do Aluno", "Notas", "Media Final");
    printf("------------------------------------------------------------------------------------\n"); // Ajustado o tamanho da linha

    for (int i = 0; i < numAlunos; ++i) {
        printf("%-25s | ", alunos[i].nome); // Alinha o nome à esquerda e adiciona separador

        // Imprime as notas com um separador claro e alinhamento
        char notas_str[150] = ""; // Buffer para construir a string de notas
        for (int j = 0; j < alunos[i].numDisciplinas; ++j) {
            char temp_nota[10];
            sprintf(temp_nota, "%.2f", alunos[i].notas[j]); // Formata a nota com 2 casas decimais
            strcat(notas_str, temp_nota);
            if (j < alunos[i].numDisciplinas - 1) {
                strcat(notas_str, " | "); // Usa " | " como separador
            }
        }
        printf("%-40s | ", notas_str); // Alinha as notas à esquerda, com 40 caracteres de largura e adiciona separador

        printf("%.2f\n", alunos[i].mediaFinal); // Imprime a média final
    }
    printf("------------------------------------------------------------------------------------\n"); // Ajustado o tamanho da linha
}

// Função para ordenar o array de alunos usando Selection Sort pela média final
// Recebe o array de alunos por referência (ponteiro para o primeiro elemento)
void selectionSort(Aluno* alunos, int numAlunos) {
    if (numAlunos <= 1) {
        printf("\nNao ha alunos suficientes para ordenar (precisa de pelo menos 2).\n");
        return;
    }

    for (int i = 0; i < numAlunos - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < numAlunos; ++j) {
            if (alunos[j].mediaFinal < alunos[minIndex].mediaFinal) {
                minIndex = j;
            }
        }
        // Troca o elemento atual com o menor elemento encontrado
        if (minIndex != i) {
            Aluno temp = alunos[i]; // Cópia rasa da struct
            alunos[i] = alunos[minIndex];
            alunos[minIndex] = temp;
        }
    }
    printf("\nAlunos ordenados pela media final (Selection Sort).\n");
}
