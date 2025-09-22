% FLL vs PLL 仿真对比
% 作者：AI 助手
% 环境：GNU Octave

clear; clc; close all;

%% 参数设置
Fs = 1000;            % 采样率 (Hz)
T = 1/Fs;             % 采样周期
t = 0:T:5;            % 时间向量 (5秒)
N = length(t);

% 输入信号：前2.5秒为 50Hz，后2.5秒跳变到 55Hz
f_in = [50*ones(1, floor(N/2)), 55*ones(1, N-floor(N/2))];
theta_in = cumsum(2*pi * f_in * T);  % 积分得到相位
u_in = sin(theta_in);               % 输入信号

%% 设计 PLL (二阶环路滤波器)
% 环路带宽和阻尼系数
Bw_pll = 10;          % PLL 带宽 (Hz)
zeta = 0.707;         % 阻尼系数
Kvco = 100;           % VCO 增益 (Hz/V)
Kd = 1;               % 鉴相器增益 (V/rad)

% 环路滤波器参数 (二阶)
a1 = (4 * Bw_pll * zeta) / (Kd * Kvco * T);
a2 = (4 * Bw_pll^2) / (Kd * Kvco * T);

% 初始化 PLL 状态
f_pll = zeros(1, N);
theta_pll = zeros(1, N);
integrated_error = 0;
phase_error = zeros(1, N);

for k = 2:N
    % 鉴相器：计算相位差 (使用反正切鉴相器近似)
    pd_output = atan2(sin(theta_in(k) - theta_pll(k-1)), cos(theta_in(k) - theta_pll(k-1)));
    phase_error(k) = pd_output;
    
    % 环路滤波器 (IIR 实现)
    integrated_error = integrated_error + a2 * phase_error(k);
    filter_output = a1 * phase_error(k) + integrated_error;
    
    % VCO：频率和相位更新
    f_pll(k) = filter_output * Kvco;
    theta_pll(k) = theta_pll(k-1) + 2*pi * f_pll(k) * T;
end

%% 设计 FLL (一阶锁频环)
% 使用频率误差检测（过零检测或鉴频器思想）
% 这里简化：用相位误差的导数估计频率误差
f_fll = zeros(1, N);
theta_fll = zeros(1, N);
fll_integrator = 0;
Kf = 0.5;  % FLL 环路增益

for k = 2:N
    % 估计频率误差：当前相位差与上一时刻相位差的变化率
    if k == 2
        freq_error = 0;
    else
        freq_error = (phase_error(k) - phase_error(k-1)) / T;
    end
    
    % FLL 积分器
    fll_integrator = fll_integrator + Kf * freq_error;
    
    % 输出频率
    f_fll(k) = fll_integrator;
    theta_fll(k) = theta_fll(k-1) + 2*pi * f_fll(k) * T;
end

%% 绘图对比

figure('Position', [100, 100, 1000, 800]);

% 子图1：输入信号与频率变化
subplot(3,2,1);
plot(t, u_in, 'Color', [0.5,0.5,0.5], 'LineWidth', 1);
hold on;
plot(t, f_in/100, 'r', 'LineWidth', 2);  % 归一化显示
xlabel('时间 (s)'); ylabel('信号 / 归一化频率');
title('输入信号与输入频率');
legend('输入信号', '输入频率 (归一化)');
grid on;

% 子图2：PLL 输出频率跟踪
subplot(3,2,2);
plot(t, f_in, 'r--', 'LineWidth', 1.5);
hold on;
plot(t, f_pll, 'b', 'LineWidth', 1.5);
xlabel('时间 (s)'); ylabel('频率 (Hz)');
title('PLL 频率跟踪');
legend('输入频率', 'PLL 输出频率');
grid on;

% 子图3：FLL 输出频率跟踪
subplot(3,2,3);
plot(t, f_in, 'r--', 'LineWidth', 1.5);
hold on;
plot(t, f_fll, 'g', 'LineWidth', 1.5);
xlabel('时间 (s)'); ylabel('频率 (Hz)');
title('FLL 频率跟踪');
legend('输入频率', 'FLL 输出频率');
grid on;

% 子图4：PLL vs FLL 频率响应对比
subplot(3,2,4);
plot(t, f_in, 'k--', 'LineWidth', 2);
hold on;
plot(t, f_pll, 'b', 'LineWidth', 1.5);
plot(t, f_fll, 'g', 'LineWidth', 1.5);
xlabel('时间 (s)'); ylabel('频率 (Hz)');
title('PLL vs FLL 频率跟踪对比');
legend('输入频率', 'PLL', 'FLL');
grid on;

% 子图5：相位误差对比
pll_phase_err = mod(theta_in - theta_pll, 2*pi);
fll_phase_err = mod(theta_in - theta_fll, 2*pi);

subplot(3,2,5);
plot(t, pll_phase_err, 'b', t, fll_phase_err, 'g');
xlabel('时间 (s)'); ylabel('相位误差 (rad)');
title('相位误差对比 (PLL vs FLL)');
legend('PLL 相位误差', 'FLL 相位误差');
grid on;

% 子图6：局部放大对比（频率跳变后）
idx_start = find(t >= 2.4, 1);
idx_end = find(t <= 2.8, 1, 'last');
subplot(3,2,6);
plot(t(idx_start:idx_end), f_in(idx_start:idx_end), 'k--', 'LineWidth', 2);
hold on;
plot(t(idx_start:idx_end), f_pll(idx_start:idx_end), 'b');
plot(t(idx_start:idx_end), f_fll(idx_start:idx_end), 'g');
xlabel('时间 (s)'); ylabel('频率 (Hz)');
title('频率跳变响应（局部放大）');
legend('输入', 'PLL', 'FLL');
grid on;

sgtitle('FLL 与 PLL 仿真对比');