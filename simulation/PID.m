# 参数设置
fs = 1; # 采样率 (Hz)，表示每秒检查一次时钟
total_time = 5000; # 总时间 (秒)
t = 0:1/fs:total_time; # 时间向量

# 参考时钟（理想时钟）
ref_clock = t;

# 本地时钟，初始频率偏差为0%
freq_offset = 0; # 无频率偏差
local_clock = zeros(size(t)); # 初始化本地时钟
local_clock(1) = ref_clock(1); # 初始时刻设为与参考时钟同步

# 控制参数
Kp = 0.01; # 比例增益
Ki = 0.0001; # 积分增益
Kd = 0.1; # 微分增益

# 存储调整后的频率和相位误差
adjusted_freqs = ones(size(t)) * (1 + freq_offset); # 初始频率
phase_errors = zeros(size(t));
integral = 0; # 累积误差初始化
prev_error = 0; # 上一时刻的误差初始化

# 循环更新本地时钟
for i = 2:length(t)
    # 计算相位误差
    phase_error = ref_clock(i-1) - local_clock(i-1);
    phase_errors(i) = phase_error;

    # 更新累积误差
    integral = integral + phase_error;

    # 计算误差变化率
    derivative = phase_error - prev_error;

    # 计算PID输出
    pid_output = Kp * phase_error + Ki * integral + Kd * derivative;

    # 根据PID输出调整频率
    adjusted_freq = 1 + freq_offset + pid_output;
    adjusted_freqs(i) = adjusted_freq;

    # 更新本地时钟
    local_clock(i) = local_clock(i-1) + adjusted_freq / fs;

    # 更新上一时刻的误差
    prev_error = phase_error;
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
