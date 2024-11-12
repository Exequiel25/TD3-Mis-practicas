import numpy as np
import matplotlib.pyplot as plt
from scipy.signal import freqz, firwin, ellip, iirfilter

# Parámetros comunes
fs = 8000  # Frecuencia de muestreo
nyq = fs / 2  # Frecuencia de Nyquist
lowcut = 300 / nyq  # Frecuencia de corte baja normalizada
highcut = 3400 / nyq  # Frecuencia de corte alta normalizada

# a) Diseño del Filtro FIR
order_fir = 101
fir_coeff = firwin(order_fir, [lowcut, highcut],
                   pass_zero=False, window='hamming')

# b) Diseño del Filtro IIR
order_iir = 6
rp = 0.5  # Ripple en la banda de paso (dB)
rs = 40  # Atenuación en la banda de rechazo (dB)
b_iir, a_iir = ellip(order_iir, rp, rs, [lowcut, highcut], btype='band')

# c) Visualización
# Respuesta en frecuencia del filtro FIR
w_fir, h_fir = freqz(fir_coeff, worN=8000)
# Respuesta en frecuencia del filtro IIR
w_iir, h_iir = freqz(b_iir, a_iir, worN=8000)

plt.figure(figsize=(12, 6))

# Graficar la respuesta en frecuencia del filtro FIR
plt.subplot(2, 1, 1)
plt.plot(w_fir, 20 * np.log10(abs(h_fir)), label='FIR')
plt.plot(w_iir, 20 * np.log10(abs(h_iir)), label='IIR')
plt.title('Respuesta en Frecuencia de Filtros Pasa-Banda')
plt.xlabel('Frecuencia [rad/muestra]')
plt.ylabel('Amplitud [dB]')
plt.grid(True)
plt.legend()
plt.axvline(lowcut * np.pi, color='red', linestyle='--')
plt.axvline(highcut * np.pi, color='red', linestyle='--')
plt.xlim(0, np.pi)

# Graficar la fase de los filtros
plt.subplot(2, 1, 2)
plt.plot(w_fir, np.angle(h_fir), label='FIR')
plt.plot(w_iir, np.angle(h_iir), label='IIR')
plt.xlabel('Frecuencia [rad/muestra]')
plt.ylabel('Fase [radianes]')
plt.grid(True)
plt.legend()
plt.xlim(0, np.pi)

plt.tight_layout()
plt.show()

# En ejercicio Profe:
f1, f2 = 300, 3400
# a-Diseñar filtro FIR (pasa-banda) ventana de Hamming, Orden 101
fir_coefs = firwin(order_fir, [f1, f2], pass_zero=False, fs=fs)

# b-Diseñar filtro IIR (pasa-banda) filtro Elíptico (Butterworth) Orden 6
iir_coefs = iirfilter(order_iir, [f1, f2], rp=rp,
                      rs=rs,  btype='band', ftype='ellip', fs=fs)

# Respuesta en frecuencia de los filtros
w_fir, h_fir = freqz(fir_coefs, worN=2000, fs=fs)
w_iir, h_iir = freqz(iir_coefs[0], iir_coefs[1], worN=2000, fs=fs)


# c-Graficar respuesta en frecuencia de los filtros
plt.figure(figsize=(12, 6))

plt.subplot(2, 1, 1)
plt.plot(w_fir, 20 * np.log10(abs(h_fir)), label='FIR')
plt.plot(w_iir, 20 * np.log10(abs(h_iir)), label='IIR')
plt.title('Rta Frecuencia Filtros Pasa-Banda: FIR (ventana de Hamming) N=101,IIR (Butterworth) O=6')
plt.xlabel('Frecuencia [Hz]')
plt.ylabel('Amplitud [dB]')
plt.grid(True)
plt.legend()
# Frecuencia de corte inferior
plt.axvline(f1, color='red', linestyle='--')
# Frecuencia de corte superior
plt.axvline(f2, color='red', linestyle='--')
plt.xlim(0, fs/2)

# Graficar fase de los filtros
plt.subplot(2, 1, 2)
plt.plot(w_fir, np.angle(h_fir), label='FIR')
plt.plot(w_iir, np.angle(h_iir), label='IIR')
plt.xlabel('Frecuencia [Hz]')
plt.ylabel('Fase [radianes]')
plt.grid(True)
plt.legend()
plt.xlim(0, fs/2)

# Mostrar gráficos
plt.tight_layout()
plt.show()
