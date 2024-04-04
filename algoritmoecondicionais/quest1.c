#include <stdio.h>

int main()
{
/* 1. Dada uma quantidade x de Megabytes (MB), converter este valor para Kilobytes (KB), para Bytes
(B) e para Gigabytes (GB). Obs.: 1 GB = 1024 MB, 1 MB = 1024 KB, 1 KB = 1024 B. */

    float v, vmb, vgb, vkb, vb;

    printf("Insira um valor em MB:  ");
    scanf("%f", &vmb);

    vkb = vmb * 1024;
    vgb = vmb / 1024;
    vb = vmb * 1024 * 1024;

    printf("O resultado é: %.2f Kilobytes, %.2f Gigabytes e %.2f Bytes.", vkb, vgb, vb);

    return 0;
}

