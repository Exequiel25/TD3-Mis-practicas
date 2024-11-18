#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

// Convertidor de punto fijo a punto flotante
double fx2fp(int32_t fixed_point, int8_t fractional_bits)
{
    return fixed_point / (double)(1 << fractional_bits); // Similar to multiply by 2^-fractional_bits
}

// Convertidor de punto flotante a punto fijo
int32_t fp2fx_rounded(double floating_point, int8_t fractional_bits)
{
    return (int32_t)round(floating_point * (1 << fractional_bits)); // Similar to multiply by 2^fractional_bits
}
int32_t fp2fx(double floating_point, int8_t fractional_bits) // Truncation
{
    return (int32_t)(floating_point * (1 << fractional_bits)); // Similar to multiply by 2^fractional_bits
}

// Redondeo por truncamiento
int32_t truncation(int64_t X, int8_t fractional_bits)
{
    // Shift the number to the right by the fractional bits
    // Is like dividing by 2^fractional_bits and discarding the remainder
    return (int32_t)(X >> fractional_bits);
}

// Redondeo al valor más cercano
int32_t rounding(int64_t X, int8_t fractional_bits)
{
    // E.g. for fractional_bits = 4
    // The unit is 1 << fractional_bits => 1.0000
    // The half is 1 << (fractional_bits - 1) => 0.1000
    // The rounding is adding the half and shifting to the right (this will get to closest)
    int64_t half = 1LL << (fractional_bits - 1);
    return (int32_t)((X + half) >> fractional_bits);
}