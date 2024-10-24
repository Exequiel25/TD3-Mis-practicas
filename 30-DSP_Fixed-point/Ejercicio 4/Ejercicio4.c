#include <stdio.h>
#include <stdint.h>
#include <limits.h>

// Función de saturación para la suma
int32_t saturation(int32_t a, int32_t b)
{
    int64_t result = (int64_t)a + (int64_t)b;

    if (result > INT_MAX)
    {
        return INT_MAX;
    }
    else if (result < INT_MIN)
    {
        return INT_MIN;
    }
    else
    {
        return (int32_t)result;
    }
}

int main()
{
    // Serie de números para verificar la función de saturación
    int32_t test_values[][2] = {
        {INT_MAX, 1},
        {INT_MIN, -1},
        {1000, 2000},
        {-1000, -2000},
        {INT_MAX / 2, INT_MAX / 2},
        {INT_MIN / 2, INT_MIN / 2},
        {INT_MAX, INT_MIN},
        {123456789, 987654321},
        {-123456789, -987654321}};

    // Verificar la función de saturación
    for (int i = 0; i < sizeof(test_values) / sizeof(test_values[0]); i++)
    {
        int32_t a = test_values[i][0];
        int32_t b = test_values[i][1];
        int32_t result = saturation(a, b);
        printf("saturation(%d, %d) = %d\n", a, b, result);
    }

    return 0;
}