#include <string.h>
#include "conversion_functions.h"

int main()
{
    // Ingrese el formato Qm.n (m.n)
    char format[10];
    printf("Ingrese el formato Qm.n (m.n): ");
    scanf("%s", format);

    // Obtener la parte entera y la parte fraccionaria
    char *integer_part = strtok(format, ".");
    char *fractional_part = strtok(NULL, ".");

    // Convertir las partes a enteros
    int8_t integer_bits = atoi(integer_part);
    int8_t fractional_bits = atoi(fractional_part);

    // Pedir el número en punto flotante
    double floating_point;
    printf("Ingrese el número en punto flotante: ");
    scanf("%lf", &floating_point);

    // Convertir el número a punto fijo
    int32_t fixed_point = fp2fx(floating_point, fractional_bits);

    // Mostrar el número en punto fijo
    printf("\nEl número en punto fijo es: %d\n", fixed_point);

    // Print the binary representation
    printf("Binary representation: ");
    for (int i = integer_bits + fractional_bits - 1; i >= 0; i--)
    {
        printf("%d", (fixed_point >> i) & 1);
    }
    printf("\n");

    // Mostrar el número en punto fijo por truncamiento
    printf("El número entero al redondear es: %d\n", rounding(fixed_point, fractional_bits));

    return 0;
}