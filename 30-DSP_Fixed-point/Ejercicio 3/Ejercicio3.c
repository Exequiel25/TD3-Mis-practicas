#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

// Definir formato Q21.10
#define Q21_10 10

// Convertidor de punto fijo a punto flotante
double fx2fp(int32_t fixed_point, int fractional_bits)
{
    return fixed_point / (double)(1 << fractional_bits);
}

// Convertidor de punto flotante a punto fijo
int32_t fp2fx(double floating_point, int fractional_bits)
{
    return (int32_t)(floating_point * (1 << fractional_bits));
}

// Redondeo por truncamiento
int32_t truncation(int64_t X)
{
    return (int32_t)(X >> Q21_10);
}

// Redondeo al valor más cercano
/*
int32_t rounding(int64_t X)
{
    return (int32_t)((X + (1 << (Q21_10 - 1))) >> Q21_10);
}
*/

// Generico
int32_t rounding(int64_t X)
{
    half = 1LL << 1;
    return (int32_t)((X + (1 << );
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Uso: %s <valor1> <valor2>\n", argv[0]);
        return 1;
    }

    double val1 = atof(argv[1]);
    double val2 = atof(argv[2]);

    // Convertir a punto fijo Q21.10
    int32_t fx_val1 = fp2fx(val1, Q21_10);
    int32_t fx_val2 = fp2fx(val2, Q21_10);

    // Multiplicar en punto fijo
    int64_t product = (int64_t)fx_val1 * fx_val2;

    // Aplicar redondeo por truncamiento
    int32_t truncated_result = truncation(product);

    // Aplicar redondeo al valor más cercano
    int32_t rounded_result = rounding(product);

    // Convertir resultados de vuelta a punto flotante
    double truncated_fp = fx2fp(truncated_result, Q21_10);
    double rounded_fp = fx2fp(rounded_result, Q21_10);
    double exact_fp = val1 * val2;

    // Imprimir resultados
    printf("Valor 1: %.10f\n", val1);
    printf("Valor 2: %.10f\n", val2);
    printf("Producto exacto (double): %.10f\n", exact_fp);
    printf("Producto truncado (Q21.10): %.10f\n", truncated_fp);
    printf("Producto redondeado (Q21.10): %.10f\n", rounded_fp);
    printf("Diferencia truncado: %.10f\n", fabs(exact_fp - truncated_fp));
    printf("Diferencia redondeado: %.10f\n", fabs(exact_fp - rounded_fp));

    return 0;
}
