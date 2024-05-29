import numpy as np

import matplotlib.pyplot as plt

# Parameters
sampling_rate = 1000  # Sampling rate in Hz
time = np.arange(0, 10, 1/sampling_rate)  # Time array

# Input signal
input_freq = 10  # Input signal frequency in Hz
input_amplitude = 1  # Input signal amplitude
input_signal = input_amplitude * np.sin(2 * np.pi * input_freq * time)

# PLL parameters
pll_freq = 10  # PLL frequency in Hz
pll_gain = 0.1  # PLL gain
pll_phase = 0  # Initial PLL phase
pll_output = np.zeros_like(time)  # PLL output signal
phase_difference = np.zeros_like(time)  # Phase difference between input and output signals
frequency_difference = np.zeros_like(time)  # Frequency difference between input and output signals

# PLL simulation
for i in range(1, len(time)):
    # Update PLL phase
    pll_phase += 2 * np.pi * pll_freq / sampling_rate + pll_gain * phase_difference[i-1]

    # Calculate PLL output signal
    pll_output[i] = np.sin(pll_phase)

    # Calculate phase difference and frequency difference
    phase_difference[i] = np.angle(input_signal[i] * np.conj(pll_output[i]))
    frequency_difference[i] = (phase_difference[i] - phase_difference[i-1]) * sampling_rate / (2 * np.pi)

# Plotting
plt.figure(figsize=(10, 6))
plt.subplot(2, 2, 1)
plt.plot(time, input_signal)
plt.title('Input Signal')
plt.xlabel('Time')
plt.ylabel('Amplitude')

plt.subplot(2, 2, 2)
plt.plot(time, pll_output)
plt.title('PLL Output Signal')
plt.xlabel('Time')
plt.ylabel('Amplitude')

plt.subplot(2, 2, 3)
plt.plot(time, phase_difference)
plt.title('Phase Difference')
plt.xlabel('Time')
plt.ylabel('Phase Difference')

plt.subplot(2, 2, 4)
plt.plot(time, frequency_difference)
plt.title('Frequency Difference')
plt.xlabel('Time')
plt.ylabel('Frequency Difference')

plt.tight_layout()
plt.show()