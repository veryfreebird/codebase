# 参数设置
fs = 1000;  # 采样频率 (Hz)
N = 10000;  # 采样点数
t = linspace(0, N/fs, N);  # 时间向量 (s)
sigma = 0.01;  # 噪声的标准差

# 生成时钟信号并添加噪声
clock_signal = t + sigma * randn(size(t));

# 计算TIE
ideal_clock = t;
TIE = clock_signal - ideal_clock;

# 绘制TIE图
figure(1);
plot(t, TIE, 'b');
title('Time Interval Error (TIE)');
xlabel('Time (s)');
ylabel('TIE (s)');

# 特定的tau值列表
specific_taus = [0.02, 0.04, 0.06, 0.1, 0.5];  # 特定的时间间隔
continuous_taus = 0.02:0.02:10;  # 连续的tau值

# 函数用于计算MTIE和TDEV
function [mtie, tdev] = calculate_mtie_tdev(TIE, fs, taus)
  n_tau = length(taus);
  mtie = zeros(1, n_tau);
  tdev = zeros(1, n_tau);
  for i = 1:n_tau
    tau = taus(i);
    tie_window = filter(ones(1, round(fs*tau)), 1, TIE);
    mtie(i) = max(tie_window) - min(tie_window);
    tdev(i) = std(tie_window, 1);
  endfor
endfunction

# 计算特定tau值下的MTIE和TDEV
[mtie_specific, tdev_specific] = calculate_mtie_tdev(TIE, fs, specific_taus);

# 绘制每个指定tau值下的peak-to-peak TIE图，并标出MTIE数值
for i = 1:length(specific_taus)
  figure(2+i);
  subplot(2,1,1);
  plot(t, TIE, 'b');
  hold on;
  plot([0, N/fs], [max(TIE), max(TIE)], 'r--');
  plot([0, N/fs], [min(TIE), min(TIE)], 'r--');
  title(['Peak-to-Peak TIE for \tau = ', num2str(specific_taus(i))]);
  xlabel('Time (s)');
  ylabel('TIE (s)');
  text(N/fs/2, (max(TIE)+min(TIE))/2, ['MTIE = ', num2str(mtie_specific(i), 3), ' s'], 'HorizontalAlignment', 'center', 'FontSize', 12);
  hold off;
  subplot(2,1,2);
  plot(t, TIE, 'b');
  hold on;
  plot([0, N/fs], [mean(TIE)-tdev_specific(i), mean(TIE)-tdev_specific(i)], 'g--');
  plot([0, N/fs], [mean(TIE)+tdev_specific(i), mean(TIE)+tdev_specific(i)], 'g--');
  title(['TDEV for \tau = ', num2str(specific_taus(i))]);
  xlabel('Time (s)');
  ylabel('TIE (s)');
  text(N/fs/2, (mean(TIE)-tdev_specific(i)+(mean(TIE)+tdev_specific(i)))/2, ['TDEV = ', num2str(tdev_specific(i), 3), ' s'], 'HorizontalAlignment', 'center', 'FontSize', 12);
  hold off;
endfor

# 计算连续tau值范围内的MTIE和TDEV
[mtie_continuous, tdev_continuous] = calculate_mtie_tdev(TIE, fs, continuous_taus);

# 在另一个图形窗口中显示连续的tau值范围内的MTIE和TDEV
figure(8);
subplot(2,1,1);
plot(continuous_taus, mtie_continuous, '-o');
title('MTIE vs. \tau');
xlabel('\tau (s)');
ylabel('MTIE (s)');

subplot(2,1,2);
plot(continuous_taus, tdev_continuous, '-o');
title('TDEV vs. \tau');
xlabel('\tau (s)');
ylabel('TDEV (s)');

# 显示所有图形
drawnow;
