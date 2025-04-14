# 参数设置
fs = 1; # 降低采样率 (Hz)，表示每秒检查一次时钟，便于观察长期效应
total_time = 100000; # 增加总时间 (秒)
t = 0:1/fs:total_time; # 时间向量

# 参考时钟（理想时钟）
ref_clock = t;

# 本地时钟，初始频率偏差为5%
freq_offset = 0.05; # 增加频率偏差比例
local_clock = zeros(size(t)); # 初始化本地时钟
local_clock(1) = 0; # 初始时刻设为0

# 较大的不对称网络时延
delay_forward = 20; # 主时钟到从时钟的时延 (秒)
delay_backward = 0; # 从时钟到主时钟的时延 (秒)

# 控制参数
Kp = 0.01; # 调整比例增益以平衡调整速度和可观测性

# 存储调整后的频率和相位误差
adjusted_freqs = ones(size(t)) * (1 + freq_offset); # 初始频率
phase_errors = zeros(size(t));

# 循环更新本地时钟
for i = 2:length(t)
    # 计算相位误差，考虑不对称时延的影响
    if mod(i, fs) == 0 % 每秒钟进行一次延迟测量
        measured_delay = delay_forward + delay_backward;
        estimated_path_delay = measured_delay / 2; # 简化的估计方法
        phase_error = ref_clock(i-1) - local_clock(i-1) - estimated_path_delay;
    else
        phase_error = ref_clock(i-1) - local_clock(i-1);
    end

    phase_errors(i) = phase_error; # 存储相位误差

    # 根据相位误差调整频率
    adjusted_freq = 1 + freq_offset + Kp * phase_error;
    adjusted_freqs(i) = adjusted_freq; # 直接存储调整后的频率

    # 更新本地时钟
    local_clock(i) = local_clock(i-1) + adjusted_freq / fs;
end

# 绘制结果
figure;
subplot(3,1,1);
plot(t, ref_clock, 'b', 'DisplayName', '参考时钟');
hold on;
plot(t, local_clock, 'r--', 'DisplayName', '调整后的本地时钟');
title('时间域波形');
xlabel('时间 (s)');
ylabel('时钟值');
legend show;

subplot(3,1,2);
plot(t, adjusted_freqs, 'g', 'DisplayName', '调整后的频率');
title('频率调整');
xlabel('时间 (s)');
ylabel('频率');

subplot(3,1,3);
plot(t, phase_errors, 'm', 'DisplayName', '相位误差');
title('相位误差');
xlabel('时间 (s)');
ylabel('相位误差 (秒)');
legend show;
