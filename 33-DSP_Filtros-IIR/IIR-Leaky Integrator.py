# Recordar que es un filtro en el DOMINIO DE TIEMPO

import numpy as np
import matplotlib.pyplot as plt
from scipy.signal import freqz, lfilter, tf2zpk
import sys


def zplane(b, a):
    """
    Plot the complex z-plane given a transfer function.
    """

    # Calculate zeros and poles
    zeros = np.roots(b)
    poles = np.roots(a)

    # Plot the unit circle
    unit_circle = plt.Circle((0, 0), 1, color='blue',
                             fill=False, linestyle='dashed')

    # Create figure and axis
    fig, ax = plt.subplots()
    ax.add_artist(unit_circle)

    # Plot zeros and poles
    plt.scatter(np.real(zeros), np.imag(zeros),
                marker='o', color='red', label='Zeros')
    plt.scatter(np.real(poles), np.imag(poles),
                marker='x', color='green', label='Poles')

    # Set labels and title
    plt.title('Pole-Zero Plot')
    plt.xlabel('Real')
    plt.ylabel('Imaginary')

    # Set equal aspect ratio
    plt.axis('equal')
    plt.xlim([-2, 2])
    plt.ylim([-2, 2])

    # Set grid
    plt.grid(which='both', color='grey', linestyle=':', linewidth=0.5)

    # Add legend
    plt.legend()

    # Show plot
    plt.show(block=False)


def leaking_integrator(lambda_val, x_noisy, fs):
    # c) Diseñar el filtro LI con λ
    b = [1 - lambda_val]
    a = [1, -lambda_val]

    # d) Graficar la respuesta en frecuencia y fase del filtro LI
    w, h = freqz(b, a, worN=8000)
    plt.figure()
    plt.subplot(2, 1, 1)
    plt.plot(0.5 * fs * w / np.pi, np.abs(h), 'b')
    plt.title(f'Respuesta en frecuencia del filtro LI con λ={lambda_val}')
    plt.xlabel('Frecuencia [Hz]')
    plt.ylabel('Amplitud')
    plt.grid()
    plt.subplot(2, 1, 2)
    plt.plot(0.5 * fs * w / np.pi, np.angle(h), 'b')
    plt.xlabel('Frecuencia [Hz]')
    plt.ylabel('Fase [radianes]')
    plt.grid()
    plt.show(block=False)

    # Determinar la frecuencia de corte fco
    fco = -np.log(lambda_val) * fs / np.pi
    print(f'Frecuencia de corte fco: {fco} Hz')

    # e) Determinar el cero y el polo del filtro y verificar su estabilidad
    z, p, k = tf2zpk(b, a)
    zplane(b, a)
    print(f'Ceros: {z}')
    print(f'Polos: {p}')
    if np.all(np.abs(p) < 1):
        print('El filtro es estable')
    else:
        print('El filtro no es estable')

    # f) Aplicar el filtro LI a la señal con ruido
    y = lfilter(b, a, x_noisy)

    # g) Graficar la respuesta en el tiempo de las señales original y filtrada
    t = np.arange(len(x_noisy)) / fs
    plt.figure()
    plt.plot(t, x_noisy, label='Señal con ruido')
    plt.plot(t, y, label='Señal filtrada')
    plt.xlabel('Tiempo [s]')
    plt.ylabel('Amplitud')
    plt.title(f'Respuesta en el tiempo con λ={lambda_val}')
    plt.legend()
    plt.grid()
    plt.show(block=False)

    # h) Graficar la respuesta en frecuencia de las señales original y filtrada
    X_noisy = np.fft.fft(x_noisy)
    Y = np.fft.fft(y)
    frequencies = np.fft.fftfreq(len(x_noisy), d=1/fs)

    plt.figure()
    plt.plot(frequencies, np.abs(X_noisy), label='Señal con ruido')
    plt.plot(frequencies, np.abs(Y), label='Señal filtrada')
    plt.xlabel('Frecuencia [Hz]')
    plt.ylabel('Amplitud')
    plt.title(f'Respuesta en frecuencia con λ={lambda_val}')
    plt.legend()
    plt.grid()
    plt.show()

    # Print memory usage
    print(f'Memory usage for filter: {
          sys.getsizeof(b) + sys.getsizeof(a)} bytes')


# Example usage
fs = 1000  # Sampling frequency
t = np.linspace(0, 1, fs, endpoint=False)  # Time vector
x = np.sin(2 * np.pi * 5 * t)  # Original signal (5 Hz sine wave)
x_noisy = x + 0.5 * np.random.randn(len(t))  # Add noise

# Repetir los pasos c) a h) para λ igual a 0.7, 0.9 y 0.98
for lambda_val in [0.7]:  # , 0.9, 0.98]:
    leaking_integrator(lambda_val, x_noisy, fs)
