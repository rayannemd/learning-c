#include <stdio.h>
#include <stdlib.h>

// definição da struct Aluno
typedef struct {
    float *notas; // ponteiro para as notas do aluno
    int num_materias; // número de matérias
} Aluno;

//calcula a media individual do aluno recebido
float calcularMediaIndividual(Aluno aluno) {
    float soma = 0;

    //notas[i] acessa a i-ésima nota do aluno, pois ponteiro notas fornece acesso direto à memória onde as notas estão armazenadas (cada linha da matriz se comporta como um array de notas). o for percorre todas as notas e soma elas.
    for (int i = 0; i < aluno.num_materias; i++) {
        soma += aluno.notas[i];
    }

    //pega a soma das notas das materias feita no for anterior e divide pelo numero de materias, calculando, assim, a sua media
    return soma / aluno.num_materias;
}

// calcula a media de notas da turma inteira, contanto com todos os alunos e todas as matérias.
float calcularMediaTurma(Aluno *alunos, int num_alunos) {
    float soma = 0;

    // percorre a linha do array (referente aos alunos) e calcula a media individual de cada aluno e soma todas as suas medias
    for (int i = 0; i < num_alunos; i++) {
        soma += calcularMediaIndividual(alunos[i]);
    }

    //pega a soma das medias do alunos e divide pela quantidade de alunos, calculando, assim, a media da turma
    return soma / num_alunos;
}

// funcao para visualizar a nota do aluno escolhido.
void visualizarNotasAluno(Aluno aluno) {
    printf("Notas do aluno:\n");
    
    //percorre e imprime as notas do aluno
    for (int j = 0; j < aluno.num_materias; j++) {
        printf("Nota na materia %d: %.2f\n", j + 1, aluno.notas[j]);
    }
}

// funcao para atualizar as notas de um aluno.
void atualizarNotasAluno(Aluno *aluno) {
    printf("Atualizando as notas do aluno:\n");
    
    //atualiza a as notas de um aluno em cada materia registrada
    for (int j = 0; j < aluno->num_materias; j++) {
        printf("Nova nota da materia %d: ", j + 1);
        scanf("%f", &aluno->notas[j]);
    }
}

// funcao para atualizar as notas da turma inteira.
void atualizarNotasTurma(Aluno *alunos, int num_alunos) {
    
    //percorre todas as colunas, atualizando a nota de cada aluno individualmente através da função atualizarNotasAluno()
    for (int i = 0; i < num_alunos; i++) {
        printf("\nAtualizando as notas do aluno %d:\n", i + 1);
        atualizarNotasAluno(&alunos[i]);
    }
}

// funcao para alterar o numero de alunos e de materias. 
void alterarQuantidade(Aluno **alunos, int *num_alunos, int *num_materias) {
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

        // realocação da matriz de alunos
        *alunos = (Aluno *)realloc(*alunos, (*num_alunos) * sizeof(Aluno));
        if (*alunos == NULL) {
            printf("Erro ao alocar memória.\n");
            // para a execução
            exit(1);
        }

        // se estamos aumentando o número de alunos
        if (*num_alunos > antigo_num_alunos) {
            //para cada novo aluno, são adicionadas as novas para a quantidade de materias existente
            for (int i = antigo_num_alunos; i < *num_alunos; i++) {
                (*alunos)[i].num_materias = *num_materias;
                (*alunos)[i].notas = (float *)malloc(*num_materias * sizeof(float));
                if ((*alunos)[i].notas == NULL) {
                    printf("Erro ao alocar memória.\n");
                    // para a execução
                    exit(1);
                }
                // recebe as notas dos novos alunos
                printf("Insira as notas do novo aluno %d:\n", i + 1);
                for (int j = 0; j < *num_materias; j++) {
                    printf("Nota da materia %d: ", j + 1);
                    scanf("%f", &(*alunos)[i].notas[j]);
                }
            }
        } else {
            // se estamos diminuindo o número de alunos, libera a memória das linhas removidas
            for (int i = *num_alunos; i < antigo_num_alunos; i++) {
                free((*alunos)[i].notas);
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
        //recebe a nova quantidade de alunos do usuario
        printf("Insira a nova quantidade de materias: ");
        scanf("%d", num_materias);

        // verifica se não foi inserida uma quantidade negativa
        if (*num_materias <= 0) {
            printf("Quantidade de materias deve ser positiva!\n");
            return;
        }

        // realocação da memória para as notas de cada aluno
        for (int i = 0; i < *num_alunos; i++) {
            (*alunos)[i].notas = (float *)realloc((*alunos)[i].notas, *num_materias * sizeof(float));
            
            // se não foi possível alocar a memoria
            if ((*alunos)[i].notas == NULL) {
                printf("Erro ao alocar memória.\n");
                // para a execução
                exit(1);
            }
            
            // atualiza o número de matérias para o aluno
            (*alunos)[i].num_materias = *num_materias;
            
            // se estamos aumentando o número de matérias
            if (*num_materias > antigo_num_materias) {
                //recebe a nova nota para a materia que foi registrada para cada aluno
                for (int j = antigo_num_materias; j < *num_materias; j++) {
                    printf("Insira a nota da materia %d para o aluno %d: ", j + 1, i + 1);
                    scanf("%f", &(*alunos)[i].notas[j]);
                } 
            }
        }
    }
}

// função para exportar notas para um arquivo txt
void exportarNotas(Aluno *alunos, int num_alunos) {

    // utilizamos o modo "w" de abertura, que é abrir um arquivo de texto para gravação. se o arquivo não existir, ele será criado. se já existir, o anterior será destruído.
    FILE *file = fopen("notas.txt", "w");

    //verifica se o arquivo foi criado
    if (file == NULL) {
        printf("Erro ao criar o arquivo.\n");
        //caso nao tenha sido, a execução é parada
        return;
    }

    //percorrerá alunos[i], que é a linha, indicando o aluno e em seguida a coluna de cada linha, que representa as notas dos alunos. ex: linha 1, posição 1: aluno 1. coluna 1: nota do aluno 1
    for (int i = 0; i < num_alunos; i++) {
        //escrevendo no arquivo, para cada aluno
        fprintf(file, "Aluno %d:\n", i + 1);
        for (int j = 0; j < alunos[i].num_materias; j++) {
            //escrevendo no arquivo, para cada nota
            fprintf(file, "Nota na materia %d: %.2f\n", j + 1, alunos[i].notas[j]);
        }
        fprintf(file, "\n");
    }

    // ao terminar de percorrer o for, irá fechar e salvar o arquivo.
    fclose(file);
    printf("Notas exportadas para 'notas.txt' com sucesso!\n");
}


int main() {
    int tam_alunos, tam_notas, opcao;

    // recebe a quantidade de alunos do usuario
    printf("Insira a quantidade de alunos: ");
    scanf("%d", &tam_alunos);

    // verifica foi inserido um numero negativo
    if (tam_alunos <= 0) {
        printf("Quantidade de alunos deve ser positiva!\n");
        // para a execução
        return 1;
    }

    // recebe a quantidade de materias do usuario
    printf("Insira a quantidade de materias: ");
    scanf("%d", &tam_notas);

    // verifica foi inserido um numero negativo
    if (tam_notas <= 0) {
        printf("Quantidade de materias deve ser positiva!\n");
        // para a execução
        return 1;
    }

    // *alunos é alocado usando malloc para criar um array de ponteiros. cada ponteiro nesse array é então alocado para criar um array de notas de matérias.
    Aluno *alunos = (Aluno *)malloc(tam_alunos * sizeof(Aluno));
    for (int i = 0; i < tam_alunos; i++) {
        alunos[i].num_materias = tam_notas;
        alunos[i].notas = (float *)malloc(tam_notas * sizeof(float));
    }

    // recebendo as notas dos alunos
    for (int i = 0; i < tam_alunos; i++) {
        printf("\nInsira as notas do aluno %d:\n", i + 1);
        for (int j = 0; j < tam_notas; j++) {
            printf("Nota da materia %d: ", j + 1);
            scanf("%f", &alunos[i].notas[j]);
        }
    }

    //utilizada para as validações que serão feitas nos casos
    int aluno;
    
    //foi utilizado um do while para que continue aparecendo o menu após acessar os casos
    do {
        printf("\nMenu:\n");
        printf("1. Calcular a media individual de um aluno\n");
        printf("2. Calcular a media da turma\n");
        printf("3. Visualizar as notas de um aluno\n");
        printf("4. Atualizar as notas de um aluno\n");
        printf("5. Atualizar as notas de toda a turma\n");
        printf("6. Alterar a quantidade de alunos e de materias\n");
        printf("7. Exportar notas da turma\n");
        printf("8. Sair\n");
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
                    printf("Media do aluno %d: %.2f\n", aluno, calcularMediaIndividual(alunos[aluno - 1]));
                }
                break;

            //caso 2 = calcular media da turma
            case 2:
                
                //imprime a media da turma, após calculá-la utilizando a função calcularMediaTurma
                printf("Media da turma: %.2f\n", calcularMediaTurma(alunos, tam_alunos));
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
                    visualizarNotasAluno(alunos[aluno - 1]);
                }
                break;

            // caso 4 = atualizar a nota de um aluno individualmente
            case 4:
                
                // recebe o numero (posição) do aluno que terá as notas atualizadas
                printf("Digite o numero do aluno para atualizar as notas (1 a %d): ", tam_alunos);
                scanf("%d", &aluno);

                //verifica se foi inserido um numero valido
                if (aluno < 1 || aluno > tam_alunos) {
                    printf("Numero do aluno invalido!\n");
                } else {
                    //chama a função atualizarNotasAluno
                    atualizarNotasAluno(&alunos[aluno - 1]);
                }
                break;

            // caso 5 = atualizar a notas da turma inteira
            case 5:
                atualizarNotasTurma(alunos, tam_alunos);
                break;

            // caso 6 = alterar quantidade
            case 6:
                alterarQuantidade(&alunos, &tam_alunos, &tam_notas);
                break;

            // caso 7 = exportar notas
            case 7:
                exportarNotas(alunos, tam_alunos);
                break;

            // sair do laço de repetição
            case 8:
                printf("Saindo...\n");

                // libera a memoria alocada 
                for (int i = 0; i < tam_alunos; i++) {
                    free(alunos[i].notas);
                }
                free(alunos);

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
