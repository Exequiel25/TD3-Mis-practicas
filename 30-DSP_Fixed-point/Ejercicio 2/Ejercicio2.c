#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

// Definir formatos Q
#define Q23_8 8
#define Q21_10 10

// Convertidor de punto fijo a punto flotante
double fx2fp(int32_t punto_fijo, int bits)
{
    return punto_fijo / (double)(1 << bits);
}

// Convertidor de punto flotante a punto fijo
int32_t fp2fx(double floating_point, int bits)
{
    return (int32_t)(floating_point * (1 << bits));
}

int main(int argc, char const *argv[])
{
    double valor_original;
    double b;
    int32_t valor_punto_fijo;

    // Verificar si se ingresó un valor por consola
    if (argc != 2)
    {
        printf("Uso: %s <valor>\n", argv[0]);
        return 1;
    }

    // Convertir el valor ingresado a punto flotante
    valor_original = atof(argv[1]);

    // Q23.8
    valor_punto_fijo = fp2fx(valor_original, Q23_8);
    b = fx2fp(valor_punto_fijo, Q23_8);
    printf("Valor Original: %.4f\n", valor_original);
    printf("Punto fijo (Q23.8): %d\n", valor_punto_fijo);
    printf("Revertido a punto flotante (Q23.8): %.4f\n", b);
    printf("Diferencia (Q23.8): %.4f\n\n", fabs(valor_original - b));

    // Q21.10
    valor_punto_fijo = fp2fx(valor_original, Q21_10);
    b = fx2fp(valor_punto_fijo, Q21_10);
    printf("Valor Original: %.4f\n", valor_original);
    printf("Punto fijo (Q21.10): %d\n", valor_punto_fijo);
    printf("Revertido a punto flotante (Q21.10): %.4f\n", b);
    printf("Diferencia (Q21.10): %.4f\n", fabs(valor_original - b));

    return 0;
}