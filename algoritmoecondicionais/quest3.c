#include <stdio.h>

int main()
{
/* 3. Dados três notas e seus pesos, calcular a média ponderada destas notas. */

    float n1, n2, n3, p1, p2, p3, mp;

    printf("Insira as notas e os pesos, respectivamente: ");
    scanf("%f, %f, %f, %f, %f, %f", &n1, &n2, &n3, &p1, &p2, &p3);

    mp = ((n1 * p1) + (n2 * p2) + (n3 * p3)) / (p1 + p2 + p3);

    printf("A media ponderada das notas e: %.2f\n", mp);

    return 0;
}s