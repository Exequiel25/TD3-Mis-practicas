import numpy as np
from scipy.signal import firwin

# Parámetros del filtro
orden = 30
frecuencia_corte = [2000]
frecuencia_muestreo = 44100  # Hz
n_coeficientes = 25
beta = 6.5

# Normalización de la frecuencia de corte
fc_normalizada = [f_corte / (frecuencia_muestreo / 2)
                  for f_corte in frecuencia_corte]

# Cálculo de los coeficientes del filtro FIR usando la ventana de Kaiser
coeff_kaiser = firwin(orden + 1, fc_normalizada, window=('kaiser', beta))

# Cálculo de los coeficientes del filtro FIR usando la ventana de Hamming
coeff_hamming = firwin(orden + 1, fc_normalizada, window='hamming')

# Cálculo de los coeficientes del filtro FIR usando la ventana de Blackman
coeff_blackman = firwin(orden + 1, fc_normalizada, window='blackman')

# Sumar los primeros 40 elementos del vector coeff para cada ventana
resp_kaiser = np.sum(coeff_kaiser[:n_coeficientes])
resp_hamming = np.sum(coeff_hamming[:n_coeficientes])
resp_blackman = np.sum(coeff_blackman[:n_coeficientes])

# Mostrar los resultados con 4 decimales
print(f'La suma de los primeros 40 elementos con ventana de Kaiser es: {
      resp_kaiser:.4f}')
print(f'La suma de los primeros 40 elementos con ventana de Hamming es: {
      resp_hamming:.4f}')
print(f'La suma de los primeros 40 elementos con ventana de Blackman es: {
      resp_blackman:.4f}')
