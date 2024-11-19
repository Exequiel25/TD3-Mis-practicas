import math

# Relación señal-ruido en dB
SNR = 110
B_ADC = 24


if B_ADC == None:
    # Fórmula para calcular el número de bits,
    # para senoidal pura: SNR_ADC = 1.76 + 6.02 * B
    B = (SNR - 1.76) / 6.02

    # Redondear al entero superior
    n_bits = math.ceil(B)

    print(f"El número mínimo de bits que debe tener el ADC es: {n_bits}")
    print("(sin 3dB de margen)")
else:
    # Fórmula para calcular bits para ruido: (SNR_ADC - SNR) / 6.02
    SNR_ADC = round(1.76 + 6.02 * B_ADC)
    print(f"La relación señal-ruido del ADC es: {SNR_ADC} dB")

    # Revisar si alcanzan los bits
    if SNR_ADC < SNR:
        print("Al ADC le faltan bits")

    B = (SNR_ADC - SNR) / 6.02

    # Redondear al entero superior
    n_bits = math.ceil(B)

    print(f"El número de bits de ruido que tiene el ADC es: {n_bits}")
