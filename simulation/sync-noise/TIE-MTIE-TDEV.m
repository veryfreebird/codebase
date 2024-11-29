

fs = 1000; % 采样频率 (Hz)
N = 10000; % 采样点数
t = (0:N-1)/fs; % 时间向量 (s)
sigma = 0.01; % 噪声的标准差

% 创建模拟相位误差数据
clock_signal = t + sigma * randn(1, N); % 模拟相位误差

% 计算TIE
ideal_clock = t;
TIE = clock_signal - ideal_clock;

% 计算 TDEV 的函数
function tdev = compute_tdev(tie, max_tau)
    taus = 1:max_tau;
    tdev = zeros(size(taus));
    for i = 1:length(taus)
        tau = taus(i);
        n = length(tie) - 2*tau;
        if n > 0
            sum_diff = 0;
            for j = 1:n
                sum_diff = sum_diff + (tie(j+2*tau) - 2*tie(j+tau) + tie(j))^2;
            end
            tdev(i) = sqrt(sum_diff / (2*n*tau^2)) ;
        else
            tdev(i) = NaN;
        end
    end
end


% 计算 MTIE 的函数
function mtie = compute_mtie(tie, max_tau)
    taus = 1:max_tau;
    mtie = zeros(size(taus));
    for i = 1:length(taus)
        tau = taus(i);
        n = length(tie) - tau;
        if n > 0
            max_peak_to_peak = 0;
            for j = 1:n
                % 计算当前窗口内的峰值到峰值值
                window_tie = tie(j:j+tau-1);
                peak_to_peak = max(window_tie) - min(window_tie);
                % 更新最大峰值到峰值值
                if peak_to_peak > max_peak_to_peak
                    max_peak_to_peak = peak_to_peak;
                end
            end
            % 保存当前 τ 间隔下的最大峰值到峰值值
            mtie(i) = max_peak_to_peak;
        else
            mtie(i) = NaN;
        end
    end
end

% 调用函数并设置最大时间间隔
max_tau = 100; % 最大时间间隔
tdev_result = compute_tdev(TIE, max_tau);
mtie_result = compute_mtie(TIE, max_tau);

% 在同一个窗口中显示TIE、MTIE和TDEV
figure;

% 绘制TIE vs Time
subplot(3,1,1); % 创建第一个子图
plot(t, TIE);
xlabel('Time (s)');
ylabel('TIE');
title('TIE vs Time');
grid on;

% 绘制MTIE vs Time Interval 使用对数刻度
subplot(3,1,2); % 创建第二个子图
semilogx(1:max_tau, mtie_result, '-o');
xlabel('Time Interval (\tau) [s]');
ylabel('MTIE');
title('MTIE vs Time Interval');
grid on;

% 绘制TDEV vs Time Interval 使用对数刻度
subplot(3,1,3); % 创建第三个子图
semilogx(1:max_tau, tdev_result, '-o');
xlabel('Time Interval (\tau) [s]');
ylabel('TDEV');
title('TDEV vs Time Interval');
grid on;
