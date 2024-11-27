% 参数设置
fs = 1000; % 采样频率 (Hz)
N = 10000; % 采样点数
t = (0:N-1)/fs; % 时间向量 (s)
sigma = 0.01; % 噪声的标准差

% 生成时钟信号并添加噪声
clock_signal = t + sigma * randn(1, N);

% 计算TIE
ideal_clock = t;
TIE = clock_signal - ideal_clock;

% 指定的tau值列表
specific_taus = [0.02, 0.06, 0.10, 0.30, 0.5]; % 特定的时间间隔
continuous_taus = 0.02:0.02:0.5; % 连续的tau值

% 创建一个新的图形窗口来显示TIE图
figure;
subplot(3,2,1);
plot(t, TIE, '-');
xlabel('Time (s)');
ylabel('TIE (s)');
title('Time Interval Error (TIE)');

% 子图索引
subplot_index = 2;

% 对每个特定tau值绘制peak-to-peak TIE
for i = 1:length(specific_taus)
    tau = specific_taus(i);
    interval_samples = round(tau * fs); % 每个间隔的样本数
    num_intervals = floor(N / interval_samples); % 区间数量
    ppTIE = zeros(num_intervals, 1); % peak-to-peak TIE数组

    for j = 1:num_intervals
        start_idx = (j-1) * interval_samples + 1;
        end_idx = min(j * interval_samples, N);
        ppTIE(j) = max(TIE(start_idx:end_idx)) - min(TIE(start_idx:end_idx));
    end

    % 找到当前tau下的MTIE
    MTIE_value = max(ppTIE);

    % 绘制peak-to-peak TIE
    subplot(3,2,subplot_index);
    bar((1:num_intervals)*tau, ppTIE, 'FaceColor', [0.5, 0.5, 0.5]);
    hold on;
    plot([0, num_intervals*tau], [MTIE_value, MTIE_value], 'r--', 'LineWidth', 2);
    xlabel(['\tau = ', num2str(tau), ' s']);
    ylabel('Peak-to-Peak TIE (s)');
    title(['\tau = ', num2str(tau), ' s Peak-to-Peak TIE']);
    text(0.05, 0.95, ['MTIE = ', num2str(MTIE_value, 4), ' s'], ...
         'Units', 'normalized', 'HorizontalAlignment', 'left', 'VerticalAlignment', 'top', 'FontSize', 10, 'Color', 'red');
    legend('Peak-to-Peak TIE per Interval', 'MTIE');
    grid on;
    xticks(0:tau:num_intervals*tau);
    xticklabels(0:tau:num_intervals*tau);
    xlim([0, num_intervals*tau]);
    hold off;
    subplot_index = subplot_index + 1;
end

% 在另一个图形窗口中绘制连续tau值与MTIE的关系图
figure;
ppTIE_max_continuous = zeros(size(continuous_taus));

for k = 1:length(continuous_taus)
    tau = continuous_taus(k);
    interval_samples = round(tau * fs); % 每个间隔的样本数
    num_intervals = floor(N / interval_samples); % 区间数量
    ppTIE = zeros(num_intervals, 1); % peak-to-peak TIE数组

    for j = 1:num_intervals
        start_idx = (j-1) * interval_samples + 1;
        end_idx = min(j * interval_samples, N);
        ppTIE(j) = max(TIE(start_idx:end_idx)) - min(TIE(start_idx:end_idx));
    end

    % 找到当前tau下的MTIE
    ppTIE_max_continuous(k) = max(ppTIE);
end

% 绘制MTIE随tau变化的曲线
plot(continuous_taus, ppTIE_max_continuous, '-o');
hold on;
xlabel('\tau (s)');
ylabel('Peak-to-peak TIE (s)');
title('MTIE for different \tau values');
grid on;


hold off;
