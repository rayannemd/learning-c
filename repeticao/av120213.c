#include <stdio.h>
#include <stdbool.h>

int main()
{
    int x, n;
    printf("Insira dois numeros: ");
    scanf("%d %d", &x, &n);

    bool primo(int num) {
        if (num < 1) {
            return false;
        }
        if (num == 1) {
            return true;
        }
        for (int i = 2; i * i <= num; i++) {
            if (num % i == 0) {
                return false;
            }
        }
        return true;
    }

    void imprimirPrimos(int x, int n) {
        int contador = 0;
        int numero = x;

        while (contador < n) {
            if (primo(numero)) {
                printf("%d ", numero);
                contador++;
            }
            numero++;
        }
        printf("\n");
    }

    printf("Os %d números primos a partir de %d são:\n", n, x);
    imprimirPrimos(x, n);

    return 0;
}
