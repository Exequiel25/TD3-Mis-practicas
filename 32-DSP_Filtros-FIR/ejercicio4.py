from scipy.signal import lfilter
from scipy.signal import firwin
import numpy as np
import matplotlib.pyplot as plt


def my_awgn(signal, snr):

    # Calculate signal power and convert to dB
    Ps = 10 * np.log10(np.mean(signal ** 2))

    # Calculate noise power and convert to dB
    Pn = Ps - snr

    # Genera ruido blanco gausiano
    noise = np.random.normal(0, np.sqrt(10 ** (Pn / 10)), signal.shape)

    # Add noise to signal
    signal_noisy = signal + noise

    return signal_noisy


# 1. Generar la onda senoidal
fs = 1000  # Frecuencia de muestreo (1000 muestras/segundo)
f = 50     # Frecuencia de la onda senoidal (50 Hz)
t = np.linspace(0, 1, fs, endpoint=False)  # 1 segundo de duración

# Onda senoidal
signal = np.sin(2 * np.pi * f * t)

snr1 = 5
snr2 = 15
snr3 = 25

# 2. Agregar ruido blanco gaussiano
# Agregar ruido utilizando la función propia
signal_noisy1 = my_awgn(signal, snr1)
signal_noisy2 = my_awgn(signal, snr2)
signal_noisy3 = my_awgn(signal, snr3)


# 3. Diseñar un filtro FIR pasa-bajo
numtaps = 10  # 10 Número de coeficientes
numtaps_50 = 50  # 50 Número de coeficientes
cutoff = 100   # Frecuencia de corte (Hz)
fir_coefs = firwin(numtaps, cutoff, fs=fs)
fir_coefs_50 = firwin(numtaps_50, cutoff, fs=fs)

# 4. Aplicar el filtro a la señal ruidosa
signal_filtered1 = lfilter(fir_coefs, 1.0, signal_noisy1)
signal_filtered2 = lfilter(fir_coefs, 1.0, signal_noisy2)
signal_filtered3 = lfilter(fir_coefs, 1.0, signal_noisy3)

signal_filtered1a = lfilter(fir_coefs_50, 1.0, signal_noisy1)
signal_filtered2a = lfilter(fir_coefs_50, 1.0, signal_noisy2)
signal_filtered3a = lfilter(fir_coefs_50, 1.0, signal_noisy3)

# 5. Graficar las señales
plt.figure(figsize=(12, 8))
plt.plot(t, signal, label='Señal Original', linewidth=2)
plt.plot(t, signal_noisy1, label='Señal con Ruido (SNR=5)', linewidth=1)
plt.plot(t, signal_filtered1, label='Señal Filtrada (N10)', linewidth=2)
plt.plot(t, signal_filtered1a, label='Señal Filtrada (N50)', linewidth=2)
plt.title('Filtración de una Onda Senoidal con Filtro FIR')
plt.xlabel('Tiempo [s]')
plt.ylabel('Amplitud')
plt.legend()
plt.grid()
plt.xlim(0, 0.2)
plt.ylim(-2, 2)
plt.show()

plt.figure(figsize=(12, 8))
plt.plot(t, signal, label='Señal Original', linewidth=2)
plt.plot(t, signal_noisy2,  label='Señal con Ruido (SNR=15)', linewidth=1)
plt.plot(t, signal_filtered2, label='Señal Filtrada (N10)', linewidth=2)
plt.plot(t, signal_filtered2a, label='Señal Filtrada (N50)', linewidth=2)
plt.title('Filtración de una Onda Senoidal con Filtro FIR')
plt.xlabel('Tiempo [s]')
plt.ylabel('Amplitud')
plt.legend()
plt.grid()
plt.xlim(0, 0.2)
plt.ylim(-2, 2)
plt.show()


plt.figure(figsize=(12, 8))
plt.plot(t, signal, label='Señal Original', linewidth=2)
plt.plot(t, signal_noisy3,  label='Señal con Ruido (SNR=25)', linewidth=1)
plt.plot(t, signal_filtered3,  label='Señal Filtrada (N10)', linewidth=2)
plt.plot(t, signal_filtered3a, label='Señal Filtrada (N50)', linewidth=2)
plt.title('Filtración de una Onda Senoidal con Filtro FIR')
plt.xlabel('Tiempo [s]')
plt.ylabel('Amplitud')
plt.legend()
plt.grid()
plt.xlim(0, 0.2)
plt.ylim(-2, 2)
plt.show()
