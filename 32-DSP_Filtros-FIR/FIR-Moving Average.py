# Recordar que es un filtro en el DOMINIO DEL TIEMPO
import numpy as np
import matplotlib.pyplot as plt
from scipy.fft import fft, fftfreq

# Generate a sample input signal (sine wave with noise)
fs = 500  # Sampling frequency
t = np.arange(0, 1.0, 1.0/fs)  # Time vector
f = 5  # Frequency of the sine wave
input_signal = np.sin(2 * np.pi * f * t) + 0.5 * np.random.randn(len(t))

# Define the Moving Average filter


def max_window_size(fs, cutoff_frequency):
    return round(np.sqrt(((0.885894**2)*fs**2)/cutoff_frequency**2) - 1)


def moving_average_filter(signal, window_size):
    # Mathematically, the moving average filter is a convolution of the signal with a rectangular window
    return np.convolve(signal, np.ones(window_size)/window_size, mode='same')


# Apply the Moving Average filter
print(f"Max window size: {max_window_size(fs, f)}")
N = 10  # Order of the filter
filtered_signal = moving_average_filter(input_signal, N)

# Plot the input signal and the filtered signal in the time domain
plt.figure(figsize=(12, 6))
plt.subplot(2, 1, 1)
plt.plot(t, input_signal, label='Input Signal')
plt.plot(t, filtered_signal, label='Filtered Signal', linestyle='--')
plt.xlabel('Time [s]')
plt.ylabel('Amplitude')
plt.title('Time Domain')
plt.legend()

# Compute the frequency response of the original and filtered signals
input_signal_fft = fft(input_signal)
filtered_signal_fft = fft(filtered_signal)
frequencies = fftfreq(len(t), 1/fs)

# Plot the frequency response
plt.subplot(2, 1, 2)
plt.plot(frequencies[:len(frequencies)//2], np.abs(input_signal_fft)
         [:len(frequencies)//2], label='Original Signal')
plt.plot(frequencies[:len(frequencies)//2], np.abs(filtered_signal_fft)
         [:len(frequencies)//2], label='Filtered Signal', linestyle='--')
plt.xlabel('Frequency [Hz]')
plt.ylabel('Magnitude')
plt.title('Frequency Domain')
plt.legend()
plt.tight_layout()
plt.show()

# Calculate the phase delay
phase_delay = np.angle(filtered_signal_fft) - np.angle(input_signal_fft)
print(f"Expected delay: {(N - 1) / (2 * fs)} s")  # Check with obtained delay

# Plot the phase response
plt.figure(figsize=(12, 6))
plt.plot(frequencies[:len(frequencies)//2], np.angle(input_signal_fft)
         [:len(frequencies)//2], label='Original Signal')
plt.plot(frequencies[:len(frequencies)//2], np.angle(filtered_signal_fft)
         [:len(frequencies)//2], label='Filtered Signal', linestyle='--')
plt.xlabel('Frequency [Hz]')
plt.ylabel('Phase [radians]')
plt.title('Phase Response')
plt.legend()
plt.tight_layout()
plt.show()

# Plot the input signal and the filtered signal with delay in the time domain
delay = (N - 1) / 2 / fs
plt.figure(figsize=(12, 6))
plt.plot(t, input_signal, label='Input Signal')
plt.plot(t - delay, filtered_signal,
         label='Filtered Signal (Delayed)', linestyle='--')
plt.xlabel('Time [s]')
plt.ylabel('Amplitude')
plt.title(f'Time Domain with Delay (Delay = {delay:.4f} s)')
plt.legend()
plt.tight_layout()
plt.show()
