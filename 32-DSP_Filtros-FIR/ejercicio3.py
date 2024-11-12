from scipy.io import loadmat
from scipy.signal import firwin, freqz, convolve
import matplotlib.pyplot as plt
import numpy as np
import sounddevice as sd


# Función para agregar ruido gaussiano
def add_gaussian_noise(signal, snr_db):
    rms_signal = np.sqrt(np.mean(signal**2))
    rms_noise = rms_signal / (10**(snr_db / 20))
    noise = np.random.normal(0, rms_noise, signal.shape)
    signal_with_noise = signal + noise
    return signal_with_noise


# Reproducción de señales
def play_audio(signal, Fs):
    sd.play(signal, Fs)
    sd.wait()


# a) Diseñar el filtro y visualizar la respuesta en frecuencia
# Parámetros del filtro
numtaps = 10
fs = 44100  # Frecuencia de muestreo en Hz
f1, f2 = 300 / (fs / 2), 3400 / (fs / 2)  # Frecuencias de corte normalizadas

# Diseño del filtro
fir_coefficients_10 = firwin(
    numtaps, [f1, f2], window='blackman', pass_zero=False)

# b) Aumentar el orden del filtro a 50 y visualizar la nueva respuesta en frecuencia
# Aumentar el orden del filtro
numtaps = 50
fir_coefficients_50 = firwin(
    numtaps, [f1, f2], window='blackman', pass_zero=False)


# c) Cargar el archivo Tchaikovsky.mat
# Cargar la señal de entrada
data = loadmat('Tchaikovsky.mat')
signal = data['signal'][:, 0]  # Seleccionar un canal de la señal estéreo

# Agregar ruido a la señal
SNR = 30
noisy_signal = add_gaussian_noise(signal, SNR)

# Filtrado con convolución
fir_output_10 = convolve(noisy_signal, fir_coefficients_10, mode='same')
fir_output_50 = convolve(noisy_signal, fir_coefficients_50, mode='same')

# Reproducir las señales (original, con ruido, y filtradas)
print("Reproduciendo señal con ruido...")
play_audio(noisy_signal, fs)
print("Reproduciendo señal filtrada con 10 coeficientes...")
play_audio(fir_output_10, fs)
print("Reproduciendo señal filtrada con 50 coeficientes...")
play_audio(fir_output_50, fs)

# d) Graficar los espectros de la señal original y filtrada
# Calcular el espectro de la señal original
frequencies, original_spectrum = freqz(signal, fs=fs)
frequencies, noisy_spectrum = freqz(noisy_signal, fs=fs)
frequencies, fir_10_spectrum = freqz(fir_output_10, fs=fs)
frequencies, fir_50_spectrum = freqz(fir_output_50, fs=fs)

# Graficar los espectros
plt.figure()
plt.plot(frequencies, np.abs(original_spectrum), label='Señal original')
plt.plot(frequencies, np.abs(noisy_spectrum), label='Señal con ruido')
plt.plot(frequencies, np.abs(fir_10_spectrum), label='Filtrada (orden 10)')
plt.plot(frequencies, np.abs(fir_50_spectrum), label='Filtrada (orden 50)')
plt.title('Espectros de la señal original y filtrada')
plt.xlabel('Frecuencia [Hz]')
plt.ylabel('Magnitud')
plt.legend()
plt.grid()
plt.show()

# Graficar la respuesta en frecuencia del filtro FIR (orden 10)
w, h = freqz(fir_coefficients_10, worN=8000)
plt.figure()
plt.plot(0.5 * fs * w / np.pi, np.abs(h), label='Orden 10')
plt.title('Respuesta en frecuencia del filtro FIR (ventana blackman) Orden 10')
plt.xlabel('Frecuencia [Hz]')
plt.ylabel('Amplitud')
plt.grid()
plt.legend()
plt.show()

# Graficar la respuesta en frecuencia del filtro FIR (orden 50)
w, h = freqz(fir_coefficients_50, worN=8000)
# Debug pirnt
print(fir_coefficients_50)
plt.figure()
plt.plot(0.5 * fs * w / np.pi, np.abs(h), label='Orden 50', color='r')
plt.title('Respuesta en frecuencia del filtro FIR (ventana blackman) Orden 50')
plt.xlabel('Frecuencia [Hz]')
plt.ylabel('Amplitud')
plt.grid()
plt.legend()
plt.show()

# e) ¿Qué diferencias observa en la señal filtrada al aumentar el orden del filtro?

# Al aumentar el orden del filtro, la señal filtrada presenta una mejor supresión
# del ruido, lo cual se traduce en una señal más limpia y con menos distorsión.
# Sin embargo, el filtro de orden 50 también introduce un mayor retardo en la señal
# filtrada, lo cual puede ser crítico en aplicaciones en tiempo real. Por otro lado,
# el filtro de orden 50 tiene una respuesta en frecuencia más selectiva, lo cual
# permite una mejor supresión del ruido en las frecuencias no deseadas.
# En general, el filtro de orden 50 ofrece un mejor rendimiento en términos de
# supresión de ruido, pero a costa de un mayor retardo y una mayor complejidad
# computacional en comparación con el filtro de orden 10.
