import numpy as np
import matplotlib.pyplot as plt
from scipy.signal import lfilter, freqz, zpk2tf, tf2zpk

# a) Generar una señal senoidal con frecuencia fundamental de 100Hz
fs = 1000  # Frecuencia de muestreo
f = 100  # Frecuencia de la señal
t = np.arange(0, 1, 1/fs)  # Vector de tiempo
x = np.sin(2 * np.pi * f * t)  # Señal senoidal

# b) Agregar ruido a la señal senoidal para obtener una SNR de 15 dB
snr = 15  # Relación señal a ruido en dB
signal_power = np.mean(x**2)
noise_power = signal_power / (10**(snr / 10))
noise = np.sqrt(noise_power) * np.random.randn(len(x))
x_noisy = x + noise


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


def leaking_integrator(lambda_val):
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
    frequencies = np.fft.fftfreq(len(x), d=1/fs)

    plt.figure()
    plt.plot(frequencies, np.abs(X_noisy), label='Señal con ruido')
    plt.plot(frequencies, np.abs(Y), label='Señal filtrada')
    plt.xlabel('Frecuencia [Hz]')
    plt.ylabel('Amplitud')
    plt.title(f'Respuesta en frecuencia con λ={lambda_val}')
    plt.legend()
    plt.grid()
    plt.show()


# Repetir los pasos c) a h) para λ igual a 0.7, 0.9 y 0.98
for lambda_val in [0.7, 0.9, 0.98]:
    leaking_integrator(lambda_val)
