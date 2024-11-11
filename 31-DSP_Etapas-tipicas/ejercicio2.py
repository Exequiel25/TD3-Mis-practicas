import numpy as np
import matplotlib.pyplot as plt
from commpy.channels import awgn
from sklearn.metrics import mean_squared_error


def my_awgn(signal, snr):
    # Calcular la potencia de la señal
    signal_power = np.var(signal)

    # Calcular la potencia del ruido a partir del SNR
    noise_power = signal_power / (10**(snr / 10))

    # Generar ruido blanco gaussiano
    noise = np.random.normal(0, np.sqrt(noise_power), signal.shape)

    # Agregar el ruido a la señal
    signal_n = signal + noise
    return signal_n


# Especificaciones
frecuencia = 100  # Frecuencia de la señal en Hz
frecuencia_muestreo = 1000  # Frecuencia de muestreo en Hz
tiempo_inicio = 0  # Tiempo de inicio en segundos
tiempo_final = 0.5  # Tiempo final en segundos

# Generar el vector de tiempo
t = np.arange(tiempo_inicio, tiempo_final, 1/frecuencia_muestreo)

# Generar la señal senoidal
signal = np.sin(2 * np.pi * frecuencia * t)

# Agregar ruido a la señal usando my_awgn
snr = 20  # Relación señal a ruido en dB
signal_n_my = my_awgn(signal, snr)

# Agregar ruido a la señal usando la función awgn de commpy
signal_n_commpy = awgn(signal, snr)

# Calcular el error cuadrático medio (RMSE)
rmse_my = np.sqrt(mean_squared_error(signal, signal_n_my))
rmse_commpy = np.sqrt(mean_squared_error(signal, signal_n_commpy))

print(f'RMSE (my_awgn): {rmse_my}')
print(f'RMSE (commpy awgn): {rmse_commpy}')

# Graficar las señales
plt.figure(figsize=(12, 6))

plt.subplot(2, 1, 1)
plt.plot(t, signal)
plt.title('Señal Original')
plt.xlabel('Tiempo (s)')
plt.ylabel('Amplitud')
plt.grid(True)

plt.subplot(2, 1, 2)
plt.plot(t, signal_n_my, label='Señal con Ruido (my_awgn)')
plt.plot(t, signal_n_commpy, label='Señal con Ruido (commpy awgn)')
plt.title('Comparación de Señales con Ruido')
plt.xlabel('Tiempo (s)')
plt.ylabel('Amplitud')
plt.legend()
plt.grid(True)

plt.tight_layout()
plt.show()
