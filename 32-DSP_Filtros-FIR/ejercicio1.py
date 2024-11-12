from scipy.signal import freqz
from scipy.signal import lfilter
import numpy as np
import matplotlib.pyplot as plt

# a) Generar una señal senoidal con frecuencia fundamental fn = 100 Hz
# Parámetros
fn = 100  # Frecuencia fundamental en Hz
fs = 1000  # Frecuencia de muestreo en Hz
t = np.arange(0, 1, 1/fs)  # Vector de tiempo de 1 segundo

# Generar señal senoidal
sine_wave = np.sin(2 * np.pi * fn * t)

# Graficar la señal senoidal
plt.plot(t, sine_wave)
plt.title('Señal Senoidal')
plt.xlabel('Tiempo [s]')
plt.ylabel('Amplitud')
plt.grid()
plt.show(block=False)

# b) Agregar ruido gaussiano a la señal senoidal
# Relación señal-ruido deseada en dB
SNR_dB = 15

# Potencia de la señal
signal_power = np.mean(sine_wave**2)

# Potencia del ruido
noise_power = signal_power / (10**(SNR_dB / 10))

# Generar ruido gaussiano
noise = np.sqrt(noise_power) * np.random.randn(len(sine_wave))

# Señal con ruido
noisy_signal = sine_wave + noise

# Graficar la señal con ruido
plt.plot(t, noisy_signal)
plt.title('Señal Senoidal con Ruido')
plt.xlabel('Tiempo [s]')
plt.ylabel('Amplitud')
plt.grid()
plt.show(block=False)

# c) Calcular el valor máximo del orden del filtro (N_max) con fco = 2 * fn
# Frecuencia de corte
fco = 2 * fn

# Calcular N_max
N_max = int(fs / fco)
print(f'N_max: {N_max}')

# d) Aplicar filtrado del tipo moving average
# Coeficientes del filtro MA
N = N_max
b = np.ones(N) / N
a = 1

# Aplicar el filtro
filtered_signal = lfilter(b, a, noisy_signal)

# Graficar la señal filtrada
plt.plot(t, filtered_signal)
plt.title('Señal Filtrada')
plt.xlabel('Tiempo [s]')
plt.ylabel('Amplitud')
plt.grid()
plt.show(block=False)

# e) Graficar la respuesta en frecuencia y fase del filtro MA
# Calcular la respuesta en frecuencia
w, h = freqz(b, a, worN=8000, fs=fs)

# Graficar la respuesta en frecuencia
plt.plot(w, 20 * np.log10(abs(h)))
plt.title('Respuesta en Frecuencia del Filtro MA')
plt.xlabel('Frecuencia [Hz]')
plt.ylabel('Amplitud [dB]')
plt.grid()
plt.show(block=False)

# f) Graficar las señales en el dominio del tiempo
plt.figure(figsize=(12, 8))

# Señal original
plt.subplot(3, 1, 1)
plt.plot(t, sine_wave)
plt.title('Señal Original')
plt.xlabel('Tiempo [s]')
plt.ylabel('Amplitud')
plt.grid()

# Señal con ruido
plt.subplot(3, 1, 2)
plt.plot(t, noisy_signal)
plt.title('Señal con Ruido')
plt.xlabel('Tiempo [s]')
plt.ylabel('Amplitud')
plt.grid()

# Señal filtrada
plt.subplot(3, 1, 3)
plt.plot(t, filtered_signal)
plt.title('Señal Filtrada')
plt.xlabel('Tiempo [s]')
plt.ylabel('Amplitud')
plt.grid()

plt.tight_layout()
plt.show(block=False)

# g) Graficar la respuesta en frecuencia de las señales original y filtrada
# Transformada de Fourier de las señales
frequencies = np.fft.fftfreq(len(t), d=1/fs)
Y_original = np.fft.fft(sine_wave)
Y_filtered = np.fft.fft(filtered_signal)

plt.figure(figsize=(12, 6))

# Señal original
plt.subplot(2, 1, 1)
plt.plot(frequencies, np.abs(Y_original))
plt.title('Respuesta en Frecuencia de la Señal Original')
plt.xlabel('Frecuencia [Hz]')
plt.ylabel('Amplitud')
plt.grid()

# Señal filtrada
plt.subplot(2, 1, 2)
plt.plot(frequencies, np.abs(Y_filtered))
plt.title('Respuesta en Frecuencia de la Señal Filtrada')
plt.xlabel('Frecuencia [Hz]')
plt.ylabel('Amplitud')
plt.grid()

plt.tight_layout()
plt.show(block=False)

# h) Repetir los puntos d) a g) para N = N_max / 2 y N = N_max * 10
# N = N_max / 2
N_half = N_max // 2
b_half = np.ones(N_half) / N_half

# N = N_max * 10
N_ten = N_max * 10
b_ten = np.ones(N_ten) / N_ten

# Filtrar con N_half
filtered_signal_half = lfilter(b_half, a, noisy_signal)

# Filtrar con N_ten
filtered_signal_ten = lfilter(b_ten, a, noisy_signal)

# Graficar las señales filtradas
plt.figure(figsize=(12, 8))

# Señal filtrada con N_half
plt.subplot(2, 1, 1)
plt.plot(t, filtered_signal_half)
plt.title('Señal Filtrada con N = N_max / 2')
plt.xlabel('Tiempo [s]')
plt.ylabel('Amplitud')
plt.grid()

# Señal filtrada con N_ten
plt.subplot(2, 1, 2)
plt.plot(t, filtered_signal_ten)
plt.title('Señal Filtrada con N = N_max * 10')
plt.xlabel('Tiempo [s]')
plt.ylabel('Amplitud')
plt.grid()

plt.tight_layout()
plt.show()
