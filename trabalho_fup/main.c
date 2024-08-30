#include <stdio.h>
#include <stdlib.h>

//calcula a media individual do aluno recebido. usa um ponteiro simples para indicar o espaço de memoria onde a primeira nota referente ao aluno está armazenada
float calcularMediaIndividual(float *notas, int num_materias) {
    float soma = 0;

    //notas[i] acessa a i-ésima nota do aluno, pois ponteiro notas fornece acesso direto à memória onde as notas estão armazenadas (cada linha da matriz se comporta como um array de notas). o for percorre todas as notas e soma elas.
    for (int i = 0; i < num_materias; i++) {
        soma += notas[i];
    }

    //pega a soma das notas das materias feita no for anterior e divide pelo numero de materias, calculando, assim, a sua media
    return soma / num_materias;
}

// calcula a media de notas da turma inteira, contanto com todos os alunos e todas as matérias. como utilizaremos a matriz notas inteira, iremos usar um ponteiro duplo, onde podemos acessar a matriz completa e suas linhas (notas dos alunos).
float calcularMediaTurma(float **notas, int num_alunos, int num_materias) {
    float soma = 0;

    // percorre a linha do array (referente aos alunos) e calcula a media individual de cada aluno e soma todas as suas medias
    for (int i = 0; i < num_alunos; i++) {
        soma += calcularMediaIndividual(notas[i], num_materias);
    }

    //pega a soma das medias do alunos e divide pela quantidade de alunos, calculando, assim, a media da turma
    return soma / num_alunos;
}

// funcao para visualizar a nota do aluno escolhido. como utilizaremos a matriz notas inteira, iremos usar um ponteiro duplo, onde podemos acessar a matriz completa e suas linhas (notas dos alunos).
void visualizarNotasAluno(float **notas, int aluno, int num_materias) {
    printf("Notas do aluno %d:\n", aluno + 1);

    //percorre e imprime as notas do aluno
    for (int j = 0; j < num_materias; j++) {
        printf("Nota na materia %d: %.2f\n", j + 1, notas[aluno][j]);
    }
}

int main() {
    int tam_alunos, tam_notas, opcao, aluno;

    // recebe a quantidade de alunos do usuario
    printf("Insira a quantidade de alunos: ");
    scanf("%d", &tam_alunos);

    // verifica foi inserido um numero negativo
    if (tam_alunos <= 0) {
        printf("Quantidade de alunos deve ser positiva!\n");
        
        return 1;
    }

    // recebe a quantidade de materias do usuario
    printf("Insira a quantidade de materias: ");
    scanf("%d", &tam_notas);

    // verifica foi inserido um numero negativo
    if (tam_notas <= 0) {
        printf("Quantidade de materias deve ser positiva!\n");
        return 1;
    }

    // **notas é alocado usando malloc para criar um array de ponteiros. cada ponteiro nesse array é então alocado para criar um array de notas de matérias.
    float **notas = (float **)malloc(tam_alunos * sizeof(float *));
    for (int i = 0; i < tam_alunos; i++) {
        notas[i] = (float *)malloc(tam_notas * sizeof(float));
    }

    // inicializa a matriz para evitar valores indefinidos
    for (int i = 0; i < tam_alunos; i++) {
        for (int j = 0; j < tam_notas; j++) {
            notas[i][j] = 0;
        }
    }

    // recebendo as notas dos alunos
    for (int i = 0; i < tam_alunos; i++) {
        printf("\nInsira as notas do aluno %d:\n", i + 1);
        for (int j = 0; j < tam_notas; j++) {
            printf("Nota da materia %d: ", j + 1);
            scanf("%f", &notas[i][j]);
        }
    }

    //foi utilizado um do while para que continue aparecendo o menu após acessar os casos
    do {
        printf("\nMenu:\n");
        printf("1. Calcular a media individual de um aluno\n");
        printf("2. Calcular a media da turma\n");
        printf("3. Visualizar as notas de um aluno\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            //caso 1 = calcular media individual do aluno
            case 1:
                // recebe a numeração do aluno que será calculada a media
                printf("Digite o numero do aluno para calcular a media (1 a %d): ", tam_alunos);
                scanf("%d", &aluno);

                //verifica se não é um tamanho invalido
                if (aluno < 1 || aluno > tam_alunos) {
                    printf("Numero do aluno invalido!\n");
                } else {
                    //imprime a media do aluno, após calculá-la na função calcularMediaIndividual()
                    printf("Media do aluno %d: %.2f\n", aluno, calcularMediaIndividual(notas[aluno - 1], tam_notas));
                }
                break;

            //caso 2 = calcular media da turma
            case 2:
                //imprime a media da turma, após calculá-la utilizando a função calcularMediaTurma
                printf("Media da turma: %.2f\n", calcularMediaTurma(notas, tam_alunos, tam_notas));
                break;

            //caso 3 = visualizar nota de um aluno
            case 3:
                // recebe a numeração do aluno que será visualizada as notas
                printf("Digite o numero do aluno para visualizar as notas (1 a %d): ", tam_alunos);
                scanf("%d", &aluno);

                //verifica se não é um tamanho invalido
                if (aluno < 1 || aluno > tam_alunos) {
                    printf("Numero do aluno invalido!\n");
                } else {
                    //acessa a função visualizarNotasAluno
                    visualizarNotasAluno(notas, aluno - 1, tam_notas);
                }
                break;

            // sair do laço de repetição
            case 4:
                printf("Saindo...\n");

                // libera a memoria alocada para a matriz notas
                for (int i = 0; i < tam_alunos; i++) {
                    free(notas[i]);
                }
                free(notas);

                //sai do laço
                break;

            // caso em que o usuario insere uma opcao invalida
            default:
                printf("Opcao invalida! Por favor, tente novamente.\n");
        }

    //enquanto a opcao nao for a de sair, o codigo continuara sendo repetido
    } while (opcao != 4);

    return 0;
}
