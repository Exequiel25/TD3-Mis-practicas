#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

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
int32_t rounding(int64_t X)
{
    return (int32_t)((X + (1 << (Q21_10 - 1))) >> Q21_10);
}

int main()
{
    // Vectores en punto flotante
    float X[5] = {1.1, 2.2, 3.3, 4.4, 5.5};
    float Y[5] = {6.6, 7.7, 8.8, 9.9, 10.1};

    // Convertir vectores a punto fijo Q21.10
    int32_t X_fx[5], Y_fx[5];
    for (int i = 0; i < 5; i++)
    {
        X_fx[i] = fp2fx(X[i], Q21_10);
        Y_fx[i] = fp2fx(Y[i], Q21_10);
    }

    // Operación MAC con redondeo por truncamiento antes de sumar
    int32_t acum_32a = 0;
    for (int i = 0; i < 5; i++)
    {
        int64_t product = (int64_t)X_fx[i] * Y_fx[i];
        acum_32a += truncation(product);
    }

    // Operación MAC con redondeo después de sumar todos los productos
    int64_t acum_64 = 0;
    for (int i = 0; i < 5; i++)
    {
        int64_t product = (int64_t)X_fx[i] * Y_fx[i];
        acum_64 += product;
    }
    int32_t acum_32b = rounding(acum_64);

    // Operación MAC en punto flotante
    double acum_db = 0.0;
    for (int i = 0; i < 5; i++)
    {
        acum_db += X[i] * Y[i];
    }

    // Convertir resultados de punto fijo a punto flotante
    double acum_32a_fp = fx2fp(acum_32a, Q21_10);
    double acum_32b_fp = fx2fp(acum_32b, Q21_10);

    // Imprimir resultados
    printf("Resultado MAC en punto flotante: %.10f\n", acum_db);
    printf("Resultado MAC con truncamiento antes de sumar (Q21.10): %.10f\n", acum_32a_fp);
    printf("Resultado MAC con redondeo después de sumar (Q21.10): %.10f\n", acum_32b_fp);
    printf("Diferencia con truncamiento: %.10f\n", fabs(acum_db - acum_32a_fp));
    printf("Diferencia con redondeo: %.10f\n", fabs(acum_db - acum_32b_fp));

    return 0;
}