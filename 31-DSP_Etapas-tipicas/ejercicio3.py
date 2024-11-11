import numpy as np
import matplotlib.pyplot as plt

# Parámetros de la onda senoidal
frecuencia = 5  # Frecuencia en Hz
tasa_muestreo = 100  # Tasa de muestreo en muestras/segundo
duracion = 1  # Duración de la señal en segundos

# Generar la onda senoidal continua
t = np.linspace(0, duracion, int(tasa_muestreo * duracion), endpoint=False)
onda_senoidal = np.sin(2 * np.pi * frecuencia * t)

# Cuantificación de la señal
niveles = [4, 8, 16]
cuantizadas = []

for nivel in niveles:
    # Definir los límites de los niveles
    limites = np.linspace(-1, 1, nivel + 1)
    # Cuantificar la señal
    indices = np.digitize(onda_senoidal, limites) - 1
    cuantizada = limites[indices]
    cuantizadas.append(cuantizada)

# Graficar la onda senoidal original y las versiones cuantificadas
plt.figure(figsize=(10, 6))
plt.plot(t, onda_senoidal, label='Original', linewidth=2)

for i, nivel in enumerate(niveles):
    plt.plot(t, cuantizadas[i], label=f'Cuantizada {nivel} niveles')

plt.xlabel('Tiempo [s]')
plt.ylabel('Amplitud')
plt.title('Cuantización de una Onda Senoidal')
plt.legend()
plt.grid(True)
plt.show()
