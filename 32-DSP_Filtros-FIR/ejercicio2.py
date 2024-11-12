import matplotlib.pyplot as plt
import sounddevice as sd
from scipy.signal import lfilter, welch
import scipy.io
import numpy as np


# Función para agregar ruido gaussiano
def add_gaussian_noise(signal, snr_db):
    rms_signal = np.sqrt(np.mean(signal**2))
    rms_noise = rms_signal / (10**(snr_db / 20))
    noise = np.random.normal(0, rms_noise, signal.shape)
    signal_with_noise = signal + noise
    return signal_with_noise


# Función para aplicar un filtro de media móvil
def moving_average_filter(signal_data, N):
    if N <= 0:
        raise ValueError(
            "El valor de N debe ser mayor que 0 para aplicar el filtro.")
    b = np.ones(N) / N
    a = 1
    filtered_signal = lfilter(b, a, signal_data)
    return filtered_signal


# Reproducir señal de audio
def play_audio(signal, Fs):
    sd.play(signal, Fs)
    sd.wait()


# a) Cargar el archivo de audio y seleccionar un canal:
# Cargar el archivo .mat
data = scipy.io.loadmat('Tchaikovsky.mat')
signal = data['signal'][:, 0]
# Cargar frecuencia de muestreo desde el archivo
Fs = int(data['Fs'][0][0])
print('Frecuencia de muestreo:', Fs)

# b) Agregar ruido gaussiano a la señal:
# Relación señal-ruido deseada en dB
SNR_dB = 50
# Señal con ruido
noisy_signal = add_gaussian_noise(signal, SNR_dB)

# c) Calcular el valor máximo de ( N ):
# Frecuencia de corte
fco = 11050
# Calcular N_max
N_max = int(Fs / fco)
print('Valor máximo de N:', N_max)

# d) Aplicar el filtro de media móvil:
# Con diferentes valores de N
filtered_signal_Nmax = moving_average_filter(noisy_signal, max(N_max, 1))
filtered_signal_Nmax_half = moving_average_filter(
    noisy_signal, max(N_max // 2, 1))
filtered_signal_Nmax_ten = moving_average_filter(
    noisy_signal, max(N_max * 10, 1))

# e) Reproducir las señales:
# Señal original
print('Reproduciendo señal original...')
play_audio(signal, Fs)
# Señal con ruido
print('Reproduciendo señal con ruido...')
play_audio(noisy_signal, Fs)
# Señales filtradas
print('Reproduciendo señal filtrada (N = N_max)...')
play_audio(filtered_signal_Nmax, Fs)
print('Reproduciendo señal filtrada (N = N_max / 2)...')
play_audio(filtered_signal_Nmax_half, Fs)
print('Reproduciendo señal filtrada (N = N_max * 10)...')
play_audio(filtered_signal_Nmax_ten, Fs)

# f) Graficar la respuesta en frecuencia:

frequences, original_spectrum = welch(signal, Fs)
_, noisy_spectrum = welch(noisy_signal, Fs)
_, filtered_spectrum_Nmax = welch(filtered_signal_Nmax, Fs)
_, filtered_spectrum_Nmax_half = welch(filtered_signal_Nmax_half, Fs)
_, filtered_spectrum_Nmax_ten = welch(filtered_signal_Nmax_ten, Fs)

plt.figure()
plt.semilogy(frequences, original_spectrum, label='Original')
plt.semilogy(frequences, noisy_spectrum, label='Con ruido')
plt.semilogy(frequences, filtered_spectrum_Nmax, label='Filtrada (N = N_max)')
plt.semilogy(frequences, filtered_spectrum_Nmax_half,
             label='Filtrada (N = N_max / 2)')
plt.semilogy(frequences, filtered_spectrum_Nmax_ten,
             label='Filtrada (N = N_max * 10)')
plt.xlabel('Frecuencia [Hz]')
plt.ylabel('Densidad espectral de potencia [V**2/Hz]')
plt.title('Densidad espectral de potencia')
plt.legend()
plt.grid()
plt.show()
