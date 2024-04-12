#include <stdio.h>

int main()
{
    char digito[100];
    int i, j, aux, tam;

    printf("Insira o digito: ");
    scanf("%s", digito);

    for(tam = 0; digito[tam] != '\0'; tam++);

    for(j = 0; j < tam-1; j++) {
        for(i = 0; i < tam-j-1; i++) {
            if(digito[i] > digito[i+1]) {
                aux = digito[i];
                digito[i] = digito[i+1];
                digito[i+1] = aux;
            }
        }
    }

    printf("Menor digito: %c\n", digito[0]);
    printf("Maior digito: %c\n", digito[tam - 1]);

    return 0;
}
