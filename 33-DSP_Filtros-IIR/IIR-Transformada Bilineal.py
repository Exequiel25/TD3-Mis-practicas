# Recordar que la transformada bilineal es una técnica para convertir un filtro analógico en un filtro digital en DOMINIO DE FRECUENCIA.
import numpy as np
from scipy.signal import cheby2, butter, cheby1, ellip

# Parámetros del filtro
orden = 20
frecuencia_corte = 9600  # Hz
frecuencia_muestreo = 48000  # Hz
ripple = 1  # dB
attenuation = 40  # dB

# Diseño del filtro Chebyshev Tipo II
sos_cheby2 = cheby2(orden, ripple, frecuencia_corte, btype='low',
                    fs=frecuencia_muestreo, output='sos')

# Diseño del filtro Butterworth
sos_butter = butter(orden, frecuencia_corte, btype='low',
                    fs=frecuencia_muestreo, output='sos')

# Diseño del filtro Chebyshev Tipo I
sos_cheby1 = cheby1(orden, ripple, frecuencia_corte, btype='low',
                    fs=frecuencia_muestreo, output='sos')

# Diseño del filtro Elíptico
sos_ellip = ellip(orden, ripple, attenuation, frecuencia_corte, btype='low',
                  fs=frecuencia_muestreo, output='sos')

# Sumar todos los elementos de la matriz SOS para cada filtro
resp_cheby2 = np.sum(sos_cheby2)
resp_butter = np.sum(sos_butter)
resp_cheby1 = np.sum(sos_cheby1)
resp_ellip = np.sum(sos_ellip)

print(f"Respuesta Chebyshev Tipo II: {resp_cheby2:.4f}")
print(f"Respuesta Butterworth: {resp_butter:.4f}")
print(f"Respuesta Chebyshev Tipo I: {resp_cheby1:.4f}")
print(f"Respuesta Elíptico: {resp_ellip:.4f}")
