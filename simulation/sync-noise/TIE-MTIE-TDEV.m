cd('/Users/freebird/src/codebase/simulation/sync-noise');

fs = 1000; % 采样频率 (Hz)
N = 1000; % 采样点数
t = (0:N-1)/fs; % 时间向量 (s)
sigma = 0.01; % 噪声的标准差

% 不同的噪声标准差
sigmas = [0.01, 0.05, 0.1]; % 三个不同的标准差

% 存储结果
mtie_results = cell(length(sigmas), 1);
tdev_results = cell(length(sigmas), 1);
TIE_results = cell(length(sigmas), 1);

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

max_tau = 999; % 最大时间间隔

% 计算不同噪声标准差下的 TIE, MTIE 和 TDEV
for k = 1:length(sigmas)
    sigma = sigmas(k);
    
    % 创建模拟相位误差数据
    clock_signal = t + sigma * randn(1, N); % 模拟相位误差
    
    % 计算TIE
    ideal_clock = t;
    TIE = clock_signal - ideal_clock;
    TIE_results{k} = TIE;
    
    % 计算 TDEV

    tdev_result = compute_tdev(TIE, max_tau);
    tdev_results{k} = tdev_result;
    
    % 计算 MTIE
    mtie_result = compute_mtie(TIE, max_tau);
    mtie_results{k} = mtie_result;
end

% 在同一个窗口中显示不同噪声标准差下的 TIE、MTIE 和 TDEV
figure;

% 找到所有 TIE, MTIE, TDEV 的最大最小值
all_TIE = vertcat(TIE_results{:});
all_MTIE = vertcat(mtie_results{:});
all_TDEV = vertcat(tdev_results{:});

min_TIE = min(all_TIE(:));
max_TIE = max(all_TIE(:));
min_MTIE = min(all_MTIE(:));
max_MTIE = max(all_MTIE(:));
min_TDEV = min(all_TDEV(:));
max_TDEV = max(all_TDEV(:));

% 绘制TIE vs Time
for k = 1:length(sigmas)
    subplot(3, length(sigmas), k);
    plot(t, TIE_results{k});
    xlabel('Time (s)');
    ylabel('TIE');
    title(['TIE vs Time (sigma = ' num2str(sigmas(k)) ')']);
    grid on;
    ylim([min_TIE max_TIE]); % 设置 y 轴限值

    % 找到当前 TIE 的最大值和最小值及其索引
    current_TIE = TIE_results{k};
    [max_val, max_idx] = max(current_TIE);
    [min_val, min_idx] = min(current_TIE);

    % 标记最大值和最小值
    hold on;
    plot(t(max_idx), max_val, 'ro', 'MarkerSize', 8, 'LineWidth', 2); % 红色标记最大值
    plot(t(min_idx), min_val, 'ro', 'MarkerSize', 8, 'LineWidth', 2); % 红色标记最小值

    % 计算最大值和最小值之间的差值
    diff_val = max_val - min_val;

    % 添加文本标注显示差值
    text_position_x = mean([t(max_idx), t(min_idx)]); % 文本标注的 x 位置
    text_position_y = max_val + 0.1 * (max_TIE - min_TIE); % 文本标注的 y 位置
    text(text_position_x, text_position_y, ['Difference: ' num2str(diff_val)], 'Color', 'r', 'FontSize', 12);
    
    % 添加最大值和最小值的 x 坐标标注
    text(t(max_idx), max_val, [' (x = ' num2str(t(max_idx)) ')'], 'Color', 'r', 'FontSize', 12, 'VerticalAlignment', 'bottom');
    text(t(min_idx), min_val, [' (x = ' num2str(t(min_idx)) ')'], 'Color', 'r', 'FontSize', 12, 'VerticalAlignment', 'top');
    hold off;
end

% 绘制MTIE vs Time Interval 使用线性刻度
for k = 1:length(sigmas)
    subplot(3, length(sigmas), length(sigmas) + k);
    semilogx((1:max_tau) / fs, mtie_results{k}, '-o'); % 使用对数刻度
    xlabel(['Time Interval (\tau) [s] - Last Value: ' num2str(mtie_results{k}(end))]);
    ylabel('MTIE');
    title(['MTIE vs Time Interval (sigma = ' num2str(sigmas(k)) ')']);
    grid on;
    ylim([min_MTIE max_MTIE]); % 设置 y 轴限值
end

% 绘制TDEV vs Time Interval 使用线性刻度
for k = 1:length(sigmas)
    subplot(3, length(sigmas), 2*length(sigmas) + k);
    semilogx((1:max_tau) / fs, tdev_results{k}, '-o'); % 使用对数刻度
    xlabel('Time Interval (\tau) [s]');
    ylabel('TDEV');
    title(['TDEV vs Time Interval (sigma = ' num2str(sigmas(k)) ')']);
    grid on;
    ylim([min_TDEV max_TDEV]); % 设置 y 轴限值
end

pause;