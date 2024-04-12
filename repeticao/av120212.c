#include <stdio.h>

int main()
{
    char digito[100];
    int i, j, aux;
    int tamanho;

    printf("Insira o digito: ");
    scanf("%s", digito);

    for(tamanho = 0; digito[tamanho] != '\0'; tamanho++);

    for(j = 0; j < tamanho-1; j++) {
        for(i = 0; i < tamanho-j-1; i++) {
            if(digito[i] > digito[i+1]) {
                aux = digito[i];
                digito[i] = digito[i+1];
                digito[i+1] = aux;
            }
        }
    }

    printf("Menor digito: %c\n", digito[0]);
    printf("Maior digito: %c\n", digito[tamanho - 1]);

    return 0;
}
