#include <stdio.h>
#include <stdlib.h>

float calcularMediaIndividual(float *notas, int num_materias) {
    float soma = 0;
    for (int i = 0; i < num_materias; i++) {
        soma += notas[i];
    }
    return soma / num_materias;
}

float calcularMediaTurma(float **notas, int num_alunos, int num_materias) {
    float soma_total = 0;
    for (int i = 0; i < num_alunos; i++) {
        soma_total += calcularMediaIndividual(notas[i], num_materias);
    }
    return soma_total / num_alunos;
}

void visualizarNotasAluno(float **notas, int aluno, int num_materias) {
    printf("Notas do aluno %d:\n", aluno + 1);
    for (int j = 0; j < num_materias; j++) {
        printf("Materia %d: %.2f\n", j + 1, notas[aluno][j]);
    }
}

int main() {
    int tam_alunos, tam_notas;
    int opcao, aluno;

    printf("Insira a quantidade de alunos: ");
    scanf("%d", &tam_alunos);
    if (tam_alunos <= 0) {
        printf("Quantidade de alunos deve ser positiva!\n");
        return 1;
    }

    printf("Insira a quantidade de materias: ");
    scanf("%d", &tam_notas);
    if (tam_notas <= 0) {
        printf("Quantidade de materias deve ser positiva!\n");
        return 1;
    }

    // Alocação dinâmica da matriz de notas
    float **notas = (float **)malloc(tam_alunos * sizeof(float *));
    for (int i = 0; i < tam_alunos; i++) {
        notas[i] = (float *)malloc(tam_notas * sizeof(float));
    }

    // Inicializar a matriz para evitar valores indefinidos
    for (int i = 0; i < tam_alunos; i++) {
        for (int j = 0; j < tam_notas; j++) {
            notas[i][j] = 0;
        }
    }

    // Recebendo as notas dos alunos
    for (int i = 0; i < tam_alunos; i++) {
        printf("\nInsira as notas do aluno %d:\n", i + 1);
        for (int j = 0; j < tam_notas; j++) {
            printf("Nota da materia %d: ", j + 1);
            scanf("%f", &notas[i][j]);
        }
    }

    do {
        printf("\nMenu:\n");
        printf("1. Calcular a media individual de um aluno\n");
        printf("2. Calcular a media da turma\n");
        printf("3. Visualizar as notas de um aluno\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                printf("Digite o numero do aluno para calcular a media (1 a %d): ", tam_alunos);
                scanf("%d", &aluno);

                if (aluno < 1 || aluno > tam_alunos) {
                    printf("Numero do aluno invalido!\n");
                } else {
                    printf("Media do aluno %d: %.2f\n", aluno, calcularMediaIndividual(notas[aluno - 1], tam_notas));
                }
                break;

            case 2:
                printf("Media da turma: %.2f\n", calcularMediaTurma(notas, tam_alunos, tam_notas));
                break;

            case 3:
                printf("Digite o numero do aluno para visualizar as notas (1 a %d): ", tam_alunos);
                scanf("%d", &aluno);

                if (aluno < 1 || aluno > tam_alunos) {
                    printf("Numero do aluno invalido!\n");
                } else {
                    visualizarNotasAluno(notas, aluno - 1, tam_notas);
                }
                break;

            case 4:
                printf("Saindo...\n");

                for (int i = 0; i < tam_alunos; i++) {
                    free(notas[i]);
                }
                free(notas);
                break;

            default:
                printf("Opcao invalida! Por favor, tente novamente.\n");
        }
    } while (opcao != 4);

    return 0;
}
