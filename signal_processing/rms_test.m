% 设置随机种子，以便每次运行结果相同
rng(1);

% 生成两个独立的高斯白噪声信号
N = 1000; % 采样点数
fs = 1000; % 假设采样频率为1000Hz
t = (0:N-1)/fs; % 时间向量
noise1 = 1 + randn(1, N); % 第一路噪声
noise2 = 2 + randn(1, N); % 第二路噪声

% 计算每个时间点的瞬时RMS值
instant_rms = sqrt((noise1.^2 + noise2.^2));

% 绘制原始噪声信号
figure;
subplot(3, 1, 1);
plot(t, noise1);
title('第一路噪声');
xlabel('时间 (s)');
ylabel('幅值');

subplot(3, 1, 2);
plot(t, noise2);
title('第二路噪声');
xlabel('时间 (s)');
ylabel('幅值');

% 绘制瞬时RMS值
subplot(3, 1, 3);
plot(t, instant_rms, 'r', 'LineWidth', 2);
title('两路噪声的瞬时RMS值');
xlabel('时间 (s)');
ylabel('瞬时RMS值');
legend('瞬时RMS值');

% 如果需要显示特定时间点的RMS值，可以取消下面这行的注释
% disp(['某一时间点的瞬时RMS值: ', num2str(instant_rms(500))]); % 例如第500个样本点
