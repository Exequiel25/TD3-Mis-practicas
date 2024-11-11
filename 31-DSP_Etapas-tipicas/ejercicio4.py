import numpy as np
import matplotlib.pyplot as plt

# Parámetros de la onda senoidal
frecuencia = 5  # Hz
tasa_muestreo = 100  # muestras/segundo
duracion = 1  # segundo

# Generar la onda senoidal continua
t = np.linspace(0, duracion, int(tasa_muestreo * duracion), endpoint=False)
onda_senoidal = np.sin(2 * np.pi * frecuencia * t)


# Función para cuantificar usando notación Q
def cuantificar(señal, bits_enteros, bits_fraccion):
    escala = 2 ** bits_fraccion  # Resolución de la parte fraccionaria
    max_val = (2 ** bits_enteros) - 1 + (1 - 1 / escala)
    min_val = - (2 ** bits_enteros)
    señal_cuantizada = np.round(señal * escala)
    señal_cuantizada = np.clip(
        señal_cuantizada, min_val * escala, max_val * escala)
    señal_cuantizada = señal_cuantizada / escala
    return señal_cuantizada


# Cuantificar usando notaciones Q3.4 y Q0.7
onda_q3_4 = cuantificar(onda_senoidal, 3, 4)
onda_q0_7 = cuantificar(onda_senoidal, 0, 7)

# Graficar la onda senoidal original y las versiones cuantificadas
plt.figure(figsize=(10, 6))
plt.plot(t, onda_senoidal, label='Original', linewidth=2)
plt.plot(t, onda_q3_4, label='Q3.4', linestyle='--', marker='o')
plt.plot(t, onda_q0_7, label='Q0.7', linestyle='--', marker='o')
plt.xlabel('Tiempo [s]')
plt.ylabel('Amplitud')
plt.title('Onda Senoidal y sus Versiones Cuantificadas')
plt.legend()
plt.grid(True)
plt.show()
