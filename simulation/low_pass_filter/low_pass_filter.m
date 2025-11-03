% Octave 代码：展示10 Hz低通滤波器的作用
% 作者：AI助手
% 日期：2025年10月30日

% 清除工作区
clear; clc; close all;

%% 1. 参数设置
fs = 300;          % 采样频率 (Hz)，远高于10 Hz以更好显示频谱
T = 100;           % 信号总时长 (秒)
t = 0:1/fs:T-1/fs; % 时间向量

fc = 10;           % 低通滤波器截止频率 (Hz)

%% 2. 生成合成的相位噪声信号
% 我们将创建一个包含以下成分的信号：
% - 一个 5 Hz 的正弦波（在通带内）
% - 一个 50 Hz 的正弦波（在阻带内）
% - 一些白噪声（代表宽带噪声）
% - 一个缓慢的漂移（如1/100 Hz的漂移）

signal_5Hz = 1.0 * sin(2*pi*5*t);           % 5 Hz 信号
signal_50Hz = 0.8 * sin(2*pi*50*t);          % 50 Hz 信号
white_noise = 0.3 * randn(size(t));          % 白噪声
slow_drift = 0.5 * sin(2*pi*0.01*t);         % 0.01 Hz 漂移

% 合成的原始相位噪声信号
original_signal = signal_5Hz + signal_50Hz + white_noise + slow_drift;

%% 3. 设计一阶10 Hz低通滤波器
% 使用巴特沃斯滤波器，一阶
order = 1;
[b, a] = butter(order, fc / (fs/2), 'low');

% 计算频率响应
[H, f] = freqz(b, a, 1024, fs);

%% 4. 应用滤波器
filtered_signal = filter(b, a, original_signal);

%% 5. 绘制图形
figure('Position', [100, 100, 1200, 800]);
set(gcf, 'Color', 'white');

% 子图1: 时域对比
subplot(2, 2, 1);
plot(t, original_signal, 'Color', [0.7, 0.7, 0.7], 'LineWidth', 0.8);
hold on;
plot(t, filtered_signal, 'b', 'LineWidth', 1.5);
xlabel('时间 (秒)');
ylabel('幅度');
title('时域信号对比');
legend('原始信号', '10 Hz低通滤波后', 'Location', 'best');
grid on;
xlim([0, 5]); % 只显示前5秒以便观察细节

% 子图2: 滤波器频率响应
subplot(2, 2, 2);
plot(f, 20*log10(abs(H)), 'r', 'LineWidth', 2);
xlabel('频率 (Hz)');
ylabel('幅度 (dB)');
title('一阶10 Hz低通滤波器频率响应');
grid on;
ylim([-40, 5]);
ax = gca;
ax.YTick = -40:10:0;
line([fc, fc], ylim, 'Color', 'k', 'LineStyle', '--', 'LineWidth', 1);
text(fc, -5, sprintf('%d Hz', fc), 'HorizontalAlignment', 'right', 'VerticalAlignment', 'middle');

% 子图3: 原始信号的频谱
subplot(2, 2, 3);
original_spectrum = abs(fft(original_signal));
f_axis = (0:length(original_spectrum)-1)*fs/length(original_spectrum);
plot(f_axis(1:500), 20*log10(original_spectrum(1:500)), 'Color', [0.7, 0.7, 0.7], 'LineWidth', 1.5);
xlabel('频率 (Hz)');
ylabel('幅度 (dB)');
title('原始信号频谱');
grid on;
% 标记关键频率
line([5, 5], ylim, 'Color', 'g', 'LineStyle', '-', 'LineWidth', 1.5);
text(5, -20, '5 Hz', 'Color', 'g', 'Rotation', 90, 'HorizontalAlignment', 'center');
line([50, 50], ylim, 'Color', 'm', 'LineStyle', '-', 'LineWidth', 1.5);
text(50, -20, '50 Hz', 'Color', 'm', 'Rotation', 90, 'HorizontalAlignment', 'center');

% 子图4: 滤波后信号的频谱
subplot(2, 2, 4);
filtered_spectrum = abs(fft(filtered_signal));
plot(f_axis(1:500), 20*log10(filtered_spectrum(1:500)), 'b', 'LineWidth', 1.5);
xlabel('频率 (Hz)');
ylabel('幅度 (dB)');
title('滤波后信号频谱');
grid on;
% 标记关键频率
line([5, 5], ylim, 'Color', 'g', 'LineStyle', '-', 'LineWidth', 1.5);
text(5, -20, '5 Hz', 'Color', 'g', 'Rotation', 90, 'HorizontalAlignment', 'center');
line([50, 50], ylim, 'Color', 'm', 'LineStyle', '-', 'LineWidth', 1.5);
text(50, -20, '50 Hz', 'Color', 'm', 'Rotation', 90, 'HorizontalAlignment', 'center');
line([fc, fc], ylim, 'Color', 'k', 'LineStyle', '--', 'LineWidth', 1);
text(fc, -5, sprintf('%d Hz', fc), 'HorizontalAlignment', 'right', 'VerticalAlignment', 'middle');

% 调整布局
tight_layout;

% 添加总标题
suptitle('10 Hz低通滤波器的作用 - 时域与频域对比', 'FontSize', 14, 'FontWeight', 'bold');

% 显示图形
print('lpf_effect.png', '-dpng', '-r300'); % 保存为高分辨率PNG
