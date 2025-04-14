# 参数设置
fs = 1000; # 采样频率 (Hz)
t = 0:1/fs:1; # 时间向量, 1秒数据
f0 = 50; # 基准频率 (Hz)

# 生成理想信号
ideal_signal = cos(2*pi*f0*t);

# 模拟动态时间误差 (DTE)
dte_amplitude = 0.001; # DTE振幅 (秒)
dte_frequency = 10; # DTE频率 (Hz)，例如每秒一次波动
dte = dte_amplitude * sin(2*pi*dte_frequency*t);

# 引入DTE后的信号
distorted_time = t + dte;
distorted_signal = cos(2*pi*f0*distorted_time);

# 叠加结果
# 注意：这里假设“叠加”是指直接将两个信号相加，这可能不是最准确的表示方法，
# 因为实际的DTE影响是通过改变信号的时间轴实现的。
combined_signal = ideal_signal + distorted_signal;

# 分析频率偏差
N = length(t);
fft_ideal = fft(ideal_signal);
fft_distorted = fft(distorted_signal);
fft_combined = fft(combined_signal);

P2_ideal = abs(fft_ideal/N);
P1_ideal = P2_ideal(1:N/2+1);
P1_ideal(2:end-1) = 2*P1_ideal(2:end-1);

P2_distorted = abs(fft_distorted/N);
P1_distorted = P2_distorted(1:N/2+1);
P1_distorted(2:end-1) = 2*P1_distorted(2:end-1);

P2_combined = abs(fft_combined/N);
P1_combined = P2_combined(1:N/2+1);
P1_combined(2:end-1) = 2*P1_combined(2:end-1);

f = fs*(0:(N/2))/N;

# 绘制时间域波形
figure;
subplot(2,1,1);
plot(t, ideal_signal, 'b', 'DisplayName', '原始信号');
hold on;
plot(t, distorted_signal - ideal_signal, 'r', 'DisplayName', 'DTE引起的偏差'); # 显示由于DTE引起的偏差
plot(t, combined_signal, 'g', 'DisplayName', '叠加后信号');
title('时间域波形');
xlabel('时间 (s)');
ylabel('幅度');
legend show;

# 绘制频谱
subplot(2,1,2);
plot(f, P1_ideal, 'b', 'DisplayName', '原始信号');
hold on;
plot(f, P1_distorted, 'r', 'DisplayName', '引入DTE后信号');
plot(f, P1_combined, 'g', 'DisplayName', '叠加后信号');
title('频谱');
xlabel('频率 (Hz)');
ylabel('|P1(f)|');
legend show;
