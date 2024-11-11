import numpy as np
import matplotlib.pyplot as plt

# Especificaciones
frecuencia = 100  # Frecuencia de la señal en Hz
frecuencia_muestreo = 1000  # Frecuencia de muestreo en Hz
tiempo_inicio = 0  # Tiempo de inicio en segundos
tiempo_final = 0.5  # Tiempo final en segundos

# Generar el vector de tiempo
t = np.arange(tiempo_inicio, tiempo_final, 1/frecuencia_muestreo)

# Generar la señal senoidal
y = np.sin(2 * np.pi * frecuencia * t)

# Graficar la señal
plt.plot(t, y)
plt.title('Señal Senoidal')
plt.xlabel('Tiempo (s)')
plt.ylabel('Amplitud')
plt.grid(True)
plt.show()