% 清除工作区变量并关闭所有图形窗口
clear all;
close all;

% 设置随机种子以确保结果可复现
rand("seed", 0);

% 时间点
t = 0:0.1:9.9;  % 从0到9.9，每0.1为一个时间单位
% 原始数据：线性增长 + 随机噪声
data = 2 * t + randn(size(t)) * 0.5;

% 绘制原始数据
figure(1);
subplot(3, 1, 1);
plot(t, data, 'b-', 'LineWidth', 2);
title('Original Data over Time');
xlabel('Time');
ylabel('Value');
grid on;

% 计算一阶差分
first_diff = diff(data);

% 由于一阶差分会减少一个数据点，我们需要调整时间轴
t_first_diff = t(1:end-1) + 0.05;  % 中心化时间轴以便于可视化

% 绘制一阶差分
subplot(3, 1, 2);
plot(t_first_diff, first_diff, 'r-', 'LineWidth', 2);
title('First Difference of the Original Data');
xlabel('Time');
ylabel('Change in Value');
grid on;

% 计算二阶差分
second_diff = diff(first_diff);

% 再次调整时间轴
t_second_diff = t_first_diff(1:end-1) + 0.05;

% 绘制二阶差分
subplot(3, 1, 3);
plot(t_second_diff, second_diff, 'g-', 'LineWidth', 2);
title('Second Difference of the Original Data');
xlabel('Time');
ylabel('Change in Change of Value');
grid on;

% 调整子图间距
set(gcf, 'Position', [100, 100, 800, 600]);