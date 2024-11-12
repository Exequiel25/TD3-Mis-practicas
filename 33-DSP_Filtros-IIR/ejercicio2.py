import sounddevice as sd
import scipy.io
import numpy as np
import matplotlib.pyplot as plt
from scipy import signal

# a) Cargar el archivo de audio
data = scipy.io.loadmat('Tchaikovsky.mat')
Fs = data['Fs'][0, 0]
audio_signal = data['signal'][:, 0]  # Seleccionar el primer canal

# b) Diseñar un filtro IIR elíptico
orden = 6
f1, f2 = 300, 3400  # Frecuencias de corte
rp = 0.5  # Ripple en la banda de paso en dB
rs = 60  # Atenuación en la banda de rechazo en dB

# Diseñar filtro pasa-banda Elliptic
b, a = signal.ellip(orden, rp, rs, [f1, f2], btype='bandpass', fs=Fs)

# Respuesta en frecuencia del filtro
w, h = signal.freqz(b, a, worN=2000)

# Graficar respuesta en frecuencia
plt.figure(figsize=(12, 6))
plt.subplot(2, 1, 1)
plt.plot(w * Fs / (2 * np.pi), 20 * np.log10(abs(h)), color='blue')
plt.title('Respuesta en Frecuencia del Filtro Elliptic Pasa-Banda')
plt.xlabel('Frecuencia [Hz]')
plt.ylabel('Amplitud [dB]')
plt.grid(True)
plt.axvline(f1, color='green')  # Frecuencia de corte inferior
plt.axvline(f2, color='green')  # Frecuencia de corte superior
plt.axhline(-rp, color='red', linestyle='--')  # Ripple de la banda de paso
# Atenuación de la banda de rechazo
plt.axhline(-rs, color='red', linestyle='--')
plt.xlim(0, Fs/2)

# Graficar respuesta de fase
plt.subplot(2, 1, 2)
plt.plot(w * Fs / (2 * np.pi), np.unwrap(np.angle(h)), color='blue')
plt.xlabel('Frecuencia [Hz]')
plt.ylabel('Fase [radianes]')
plt.grid(True)
plt.xlim(0, Fs/2)
plt.tight_layout()
plt.show()

# c) Aumentar el orden del filtro a 12
orden = 12
b, a = signal.ellip(orden, rp, rs, [f1, f2], btype='bandpass', fs=Fs)

# Respuesta en frecuencia del filtro con orden 12
w, h = signal.freqz(b, a, worN=2000)

# Graficar respuesta en frecuencia con orden 12
plt.figure(figsize=(12, 6))
plt.subplot(2, 1, 1)
plt.plot(w * Fs / (2 * np.pi), 20 * np.log10(abs(h)), color='blue')
plt.title('Respuesta en Frecuencia del Filtro Elliptic Pasa-Banda (Orden 12)')
plt.xlabel('Frecuencia [Hz]')
plt.ylabel('Amplitud [dB]')
plt.grid(True)
plt.axvline(f1, color='green')  # Frecuencia de corte inferior
plt.axvline(f2, color='green')  # Frecuencia de corte superior
plt.axhline(-rp, color='red', linestyle='--')  # Ripple de la banda de paso
# Atenuación de la banda de rechazo
plt.axhline(-rs, color='red', linestyle='--')
plt.xlim(0, Fs/2)

# Graficar respuesta de fase con orden 12
plt.subplot(2, 1, 2)
plt.plot(w * Fs / (2 * np.pi), np.unwrap(np.angle(h)), color='blue')
plt.xlabel('Frecuencia [Hz]')
plt.ylabel('Fase [radianes]')
plt.grid(True)
plt.xlim(0, Fs/2)
plt.tight_layout()
plt.show()

# d) Convertir los coeficientes b y a a la representación SOS
sos = signal.tf2sos(b, a)

# e) Filtrar la señal de entrada usando la representación SOS
y = signal.sosfilt(sos, audio_signal)

# f) Graficar los espectros de la señal original y filtrada
plt.figure(figsize=(12, 6))
plt.subplot(2, 1, 1)
plt.magnitude_spectrum(audio_signal, Fs=Fs, scale='dB', color='blue')
plt.title('Espectro de la Señal Original')
plt.xlabel('Frecuencia [Hz]')
plt.ylabel('Amplitud [dB]')
plt.grid(True)

plt.subplot(2, 1, 2)
plt.magnitude_spectrum(y, Fs=Fs, scale='dB', color='blue')
plt.title('Espectro de la Señal Filtrada')
plt.xlabel('Frecuencia [Hz]')
plt.ylabel('Amplitud [dB]')
plt.grid(True)

plt.tight_layout()
plt.show()

# g) Examinar ambas gráficas y observar las diferencias
# La señal filtrada debería mostrar una atenuación significativa fuera de las frecuencias de corte del filtro.
