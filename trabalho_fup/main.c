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

// funcao para atualizar as notas de um aluno. como precisaremos consultar a matriz notas inteira, iremos usar um ponteiro duplo, onde podemos acessar a matriz completa e suas linhas (notas dos alunos).
void atualizarNotasAluno(float **notas, int aluno, int num_materias) {
    printf("Atualizando as notas do aluno %d:\n", aluno + 1);

    //atualiza a as notas de um aluno em cada materia registrada
    for (int j = 0; j < num_materias; j++) {
        printf("Nova nota da materia %d: ", j + 1);
        scanf("%f", &notas[aluno][j]);
    }
}

// funcao para atualizar as notas da turma inteira. como precisaremos consultar a matriz notas inteira, iremos usar um ponteiro duplo, onde podemos acessar a matriz completa e suas linhas (notas dos alunos).
void atualizarNotasTurma(float **notas, int num_alunos, int num_materias) {
    //percorre as linhas (alunos)
    for (int i = 0; i < num_alunos; i++) {
        printf("\nAtualizando as notas do aluno %d:\n", i + 1);
        //percorre as materias (notas em cada materia)
        for (int j = 0; j < num_materias; j++) {
            printf("Nova nota da materia %d: ", j + 1);
            scanf("%f", &notas[i][j]);
        }
    }
}

// funcao para alterar o numero de alunos e de materias. como precisaremos consultar a matriz notas inteira, iremos usar um ponteiro duplo, onde podemos acessar a matriz completa e suas linhas (notas dos alunos).
void alterarQuantidade(float ***notas, int *num_alunos, int *num_materias) {
    int alterarAlunos, alterarMaterias;

    // pergunta se deseja alterar a quantidade de alunos
    printf("Deseja alterar a quantidade de alunos (1 - Sim, 0 - Nao)? ");
    scanf("%d", &alterarAlunos);

    // se o usuário deseja alterar a quantidade de alunos
    if (alterarAlunos) {
        //variavel para ser usada na comparação posteriormente
        int antigo_num_alunos = *num_alunos;
        //recebe a nova quantidade de alunos do usuario
        printf("Insira a nova quantidade de alunos: ");
        scanf("%d", num_alunos);

        // verifica se foi inserida uma quantidade negativa
        if (*num_alunos <= 0) {
            printf("Quantidade de alunos deve ser positiva!\n");
            return;
        }

        // realoca a matriz de ponteiros para os alunos
        *notas = (float **)realloc(*notas, (*num_alunos) * sizeof(float *));
        if (*notas == NULL) {
            printf("Erro ao alocar memória.\n");
            exit(1);
        }

        // se estamos AUMENTANDO o número de alunos
        if (*num_alunos > antigo_num_alunos) {
            // aloca memoria para as novas linhas de notas
            for (int i = antigo_num_alunos; i < *num_alunos; i++) {
                (*notas)[i] = (float *)malloc(*num_materias * sizeof(float));
                if ((*notas)[i] == NULL) {
                    printf("Erro ao alocar memória.\n");
                    exit(1);
                }
                // recebe as notas dos novos alunos para cada aluno adicionado
                printf("Insira as notas do novo aluno %d:\n", i + 1);
                for (int j = 0; j < *num_materias; j++) {
                    printf("Nota da materia %d: ", j + 1);
                    scanf("%f", &(*notas)[i][j]);
                }
            }
        } else {
            // se estamos diminuindo o número de alunos, libera a memória das linhas removidas
            for (int i = *num_alunos; i < antigo_num_alunos; i++) {
                free((*notas)[i]);
            }
        }
    }

    // pergunta se deseja alterar a quantidade de materias
    printf("Deseja alterar a quantidade de materias (1 - Sim, 0 - Nao)? ");
    scanf("%d", &alterarMaterias);

    // se o usuario deseja alterar a quantidade de materias
    if (alterarMaterias) {
        //variavel para ser usada na comparação posteriormente
        int antigo_num_materias = *num_materias;
        //recebe a nova quantidade de materias
        printf("Insira a nova quantidade de materias: ");
        scanf("%d", num_materias);

        // verifica se foi inserida uma quantidade negativa
        if (*num_materias <= 0) {
            printf("Quantidade de materias deve ser positiva!\n");
            return;
        }

        // realoca a memória para as notas de cada aluno
        for (int i = 0; i < *num_alunos; i++) {
            (*notas)[i] = (float *)realloc((*notas)[i], *num_materias * sizeof(float));
            if ((*notas)[i] == NULL) {
                printf("Erro ao alocar memória.\n");
                exit(1);
            }

            // se estamos aumentando o número de matérias
            if (*num_materias > antigo_num_materias) {
                // Solicita as notas adicionais para todas as matérias novas
                for (int j = antigo_num_materias; j < *num_materias; j++) {
                    //recebe a nova nota para a materia que foi registrada para cada aluno
                    printf("Insira a nota da materia %d para o aluno %d: ", j + 1, i + 1);
                    scanf("%f", &(*notas)[i][j]);
                }
            // OBSERVACAO: se estivermos diminuindo o numero de materias, nao se faz necessario liberar a memoria, pois o realloc já ajusta o tamanho da memória realocada e a memória é liberada de forma segura
            }
        }
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
        printf("4. Atualizar as notas de um aluno\n");
        printf("5. Atualizar as notas de toda a turma\n");
        printf("6. Alterar a quantidade de alunos e de materias\n");
        printf("7. Sair\n");
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

            // caso 4 = atualizar a nota de um aluno individualmente
            case 4:
                printf("Digite o numero do aluno para atualizar as notas (1 a %d): ", tam_alunos);
                scanf("%d", &aluno);

                //verifica se foi inserido um numero valido
                if (aluno < 1 || aluno > tam_alunos) {
                    printf("Numero do aluno invalido!\n");
                } else {
                    //chama a função atualizarNotasAluno
                    atualizarNotasAluno(notas, aluno - 1, tam_notas);
                }
                break;

            // caso 5 = atualizar a notas da turma inteira
            case 5:
                atualizarNotasTurma(notas, tam_alunos, tam_notas);
                break;

            // caso 6 = alterar quantidade
            case 6:
                alterarQuantidade(&notas, &tam_alunos, &tam_notas);
                break;


            // sair do laço de repetição
            case 7:
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
    } while (opcao != 7);

    return 0;
}
