import numpy as np
import matplotlib.pyplot as plt
# Define the input signal parameters
input_frequency = 1  # Input signal frequency in Hz
input_amplitude = 1  # Input signal amplitude
input_phase = 2  # Input signal phase in radians
# Define the PLL parameters
sampling_frequency = 1000  # Sampling frequency in Hz
loop_gain = 0.1  # Loop gain
damping_factor = 0.707  # Damping factor
natural_frequency = 2 * np.pi * 10  # Natural frequency in rad/s
# Generate the time vector
time = np.arange(0, 10, 1 / sampling_frequency)
# Generate the input signal
input_signal = input_amplitude * np.sin(2 * np.pi * input_frequency * time + input_phase)
# Initialize the PLL variables
output_signal = np.zeros_like(time)
phase_difference = np.zeros_like(time)
filtered_error = 0
vco_frequency = 0
# Run the PLL loop
for i in range(len(time)):
    # Calculate the phase difference
    phase_difference[i] = np.arctan2(np.sin(vco_frequency * time[i]), np.cos(vco_frequency * time[i])) - np.arctan2(input_signal[i], filtered_error)
    # Update the filtered error
    filtered_error += loop_gain * phase_difference[i]
    # Update the VCO frequency
    vco_frequency = natural_frequency + damping_factor * filtered_error
    # Generate the output signal
    output_signal[i] = input_amplitude * np.sin(2 * np.pi * vco_frequency * time[i] + input_phase)
# Plot the input signal, output signal, and phase difference
plt.figure(figsize=(10, 6))
plt.subplot(3, 1, 1)
plt.plot(time, input_signal)
plt.title('Input Signal')
plt.xlabel('Time')
plt.ylabel('Amplitude')
plt.subplot(3, 1, 2)
plt.plot(time, output_signal)
plt.title('Output Signal')
plt.xlabel('Time')
plt.ylabel('Amplitude')
plt.subplot(3, 1, 3)
plt.plot(time, phase_difference)
plt.title('Phase Difference')
plt.xlabel('Time')
plt.ylabel('Phase Difference (radians)')
plt.tight_layout()
plt.show()