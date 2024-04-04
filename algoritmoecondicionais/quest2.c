#include <stdio.h>

int main()
{
/* 2. Dado o tempo de uma receita em horas e minutos (Ex.: 1h e 40min), converter esse tempo em
segundos. */

    int h, hs, m, ms, s;

    printf("Insira o tempo da receita : ");
    scanf("%dh e %dm", &h, &m);

    hs = h * 60 * 60;
    ms = m * 60;
    s = hs + ms;

    printf("Faltam %d segundos para o bolo ficar pronto", s);

    return 0;
}