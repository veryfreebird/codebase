% 定义信号参数
fs = 44100; % 采样率 (Hz)
t = linspace(0, 1, fs); % 时间向量，持续1秒
f = 220; % 信号频率 (Hz)
A = 1; % 信号幅度
phi = pi/4; % 初始相位，这里设置为45度

% 生成复数信号
y = A * exp(1i * 2 * pi * f * t + 1i * phi);

% 可视化实部和虚部
subplot(2,1,1);
plot(t, real(y));
xlabel('Time (s)');
ylabel('Real Part');
title('Real Part of the Complex Signal');

subplot(2,1,2);
plot(t, imag(y));
xlabel('Time (s)');
ylabel('Imaginary Part');
title('Imaginary Part of the Complex Signal');

% 或者可视化信号的幅度和相位
figure;
subplot(2,1,1);
plot(t, abs(y));
xlabel('Time (s)');
ylabel('Magnitude');
title('Magnitude of the Complex Signal');

subplot(2,1,2);
plot(t, angle(y) * 180/pi);
xlabel('Time (s)');
ylabel('Phase (degrees)');
title('Phase of the Complex Signal');