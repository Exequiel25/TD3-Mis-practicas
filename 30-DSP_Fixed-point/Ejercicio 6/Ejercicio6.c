#include <stdio.h>
#include <stdint.h>

int main()
{
    /*
    Suponga que debe implementar un filtro digital con un procesador DSP de 16 bits.
    El mismo cuenta con un acumulador de 40 bits en su ALU.
    Calcule cuántas sumas consecutivas puede realizar garantizando que no se producirá un overflow.

    1) Determinar el Rango de Valores de 16 Bits
        - Enteros con signo (signed): -32768 a 32767 (-2^15 a 2^15 - 1)

    2) Determinar el Rango del Acumulador de 40 Bits
        - Enteros con signo (signed): -549,755,813,888 a 549,755,813,887 (-2^39 a 2^39 - 1)

    3) Calcular el Número Máximo de Sumas Consecutivas:
        - Número Máximo de Sumas = (Máximo Acumulador) / (Máximo Valor de 16 Bits)
    */
    int64_t max_accumulator_value = (1LL << 39) - 1; // 2^39 - 1
    int16_t max_16bit_value = 32767;

    int64_t max_sums = max_accumulator_value / max_16bit_value;

    printf("Número máximo de sumas consecutivas sin overflow: %ld\n", max_sums);

    return 0;
}