import numpy as np
import matplotlib.pyplot as plt

# Parámetros
f1 = 45  # Frecuencia de la primera onda senoidal
f2 = 55  # Frecuencia de la segunda onda senoidal
fs1 = 50  # Primera tasa de muestreo
fs2 = 100  # Segunda tasa de muestreo
t = np.linspace(0, 1, 1000, endpoint=False)  # Tiempo continuo

# Generar onda senoidal continua
sine_wave1 = np.sin(2 * np.pi * f1 * t)

# Muestrear la onda senoidal a fs1 y fs2
t_fs1 = np.arange(0, 1, 1/fs1)
t_fs2 = np.arange(0, 1, 1/fs2)
sine_wave1_fs1 = np.sin(2 * np.pi * f1 * t_fs1)
sine_wave1_fs2 = np.sin(2 * np.pi * f1 * t_fs2)

# Graficar la onda continua y las versiones muestreadas
plt.figure(figsize=(10, 6))
plt.plot(t, sine_wave1, label='Onda continua 45 Hz')
plt.plot(t_fs1, sine_wave1_fs1, 'r--o', label='Muestreo a 50 Hz')
plt.plot(t_fs2, sine_wave1_fs2, 'g--x', label='Muestreo a 100 Hz')
plt.xlabel('Tiempo [s]')
plt.ylabel('Amplitud')
plt.title('Onda senoidal continua y muestreada (45 Hz)')
plt.legend()
plt.grid()
plt.show(block=False)

# Generar segunda onda senoidal continua
sine_wave2 = np.sin(2 * np.pi * f2 * t)
sine_wave2_fs1 = np.sin(2 * np.pi * f2 * t_fs1)

# Graficar la segunda onda continua y su versión muestreada
plt.figure(figsize=(10, 6))
plt.plot(t, sine_wave2, label='Onda continua 55 Hz')
plt.plot(t_fs1, sine_wave2_fs1, 'r-o', label='Muestreo a 50 Hz')
plt.xlabel('Tiempo [s]')
plt.ylabel('Amplitud')
plt.title('Onda senoidal continua y muestreada (55 Hz)')
plt.legend()
plt.grid()
plt.show(block=False)

# Comparar las versiones muestreadas de las dos ondas senoidales a fs1
plt.figure(figsize=(10, 6))
plt.plot(t_fs1, sine_wave1_fs1, 'r-o', label='Onda 45 Hz muestreada a 50 Hz')
plt.plot(t_fs1, sine_wave2_fs1, 'b-o', label='Onda 55 Hz muestreada a 50 Hz')
plt.xlabel('Tiempo [s]')
plt.ylabel('Amplitud')
plt.title('Comparación de ondas muestreadas a 50 Hz')
plt.legend()
plt.grid()
plt.show()
