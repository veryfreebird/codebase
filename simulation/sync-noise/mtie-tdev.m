% 生成一些示例数据
t = 0:1:1000;  % 时间点，单位可以是秒
phase_diff = cumsum(randn(1, length(t)));  % 随机生成的相位差数据

% 计算TDEV
function [tdev, tau] = tdev(phase_diff, max_tau)
    n = length(phase_diff);
    tdev = zeros(1, max_tau-1);
    for i = 2:max_tau
        m = floor(n / i);
        sum_squares = 0;
        for j = 1:m
            sum_squares = sum_squares + (phase_diff(j*i) - 2*phase_diff((j-1)*i+floor(i/2)+1) + phase_diff((j-1)*i+1))^2;
        end
        tdev(i-1) = sqrt(sum_squares / (2 * m * i^2));
    end
    tau = 1:max_tau-1;
end

% 计算MTIE
function [mtie, tau] = mtie(phase_diff, max_tau)
    n = length(phase_diff);
    mtie = zeros(1, max_tau-1);
    for i = 2:max_tau
        m = floor(n / i);
        max_error = 0;
        for j = 1:m
            error = abs(cumsum(diff(phase_diff((j-1)*i+1:j*i))));
            if max(error) > max_error
                max_error = max(error);
            end
        end
        mtie(i-1) = max_error;
    end
    tau = 1:max_tau-1;
end

% 设置最大tau值
max_tau = 100;

% 调用函数计算TDEV
[tdev, tau] = tdev(phase_diff, max_tau);

% 调用函数计算MTIE
[mtie, tau] = mtie(phase_diff, max_tau);

% 计算TIE
tie = diff(phase_diff);  % TIE是相位差的差分

% 绘制TDEV、TIE和MTIE图
figure;
subplot(3, 1, 1);
plot(t(2:end), tie, 'r-');
title('Time Interval Error (TIE)');
xlabel('Time (s)');
ylabel('TIE');
grid on;

subplot(3, 1, 2);
semilogx(tau, mtie, 'g-');  % 使用半对数坐标系
title('Maximum Time Interval Error (MTIE)');
xlabel('Tau (s)');
ylabel('MTIE');
grid on;

subplot(3, 1, 3);
semilogx(tau, tdev, 'b-');  % 使用半对数坐标系
title('Time Deviation (TDEV)');
xlabel('Tau (s)');
ylabel('TDEV');
grid on;

% 保持图形窗口打开
% pause;
