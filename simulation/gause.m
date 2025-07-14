% 设置图形大小和分辨率
set(groot, "defaultfiguresize", "[1200x800]");
set(groot, "defaultlineaxesresampaix", "on");
set(groot, "defaultlineaxesresampy", "on");

% 绘制正态分布曲线
x = linspace(-4, 4, 1000);
mu = 0;
sigma = 1;

pdf = normpdf(x, mu, sigma);

figure(1);
title("标准正态分布曲线", "fontsize", 20);
xlabel("x", "fontsize", 16);
ylabel("概率密度", "fontsize", 16);

% 绘制曲线
plot(x, pdf, 'b-', 'linewidth', 2);

% 标注平均值和标准差的位置
hold on;

% 平均值 (μ)
mu_line = mu;
plot([mu_line, mu_line], [0, max(pdf)], 'black--', 'linewidth', 2);
text(mu_line + 0.1, -0.05, "μ", "fontsize", 18);

% 标准差的位置
sigma = 1;

% ±1σ
x1 = [mu - sigma, mu + sigma];
plot(x1, [0, 0], 'red:', 'linewidth', 2);
fill([mu - sigma, mu + sigma], [0, 0], [], 'red', 0.3);
text(mu - sigma + 0.15, -0.1, "1σ", "fontsize", 14);

% ±2σ
x2 = [mu - 2*sigma, mu + 2*sigma];
plot(x2, [0, 0], 'green:', 'linewidth', 2);
fill([mu - 2*sigma, mu + 2*sigma], [0, 0], [], 'green', 0.3);
text(mu - 2*sigma + 0.15, -0.1, "2σ", "fontsize", 14);

% ±3σ
x3 = [mu - 3*sigma, mu + 3*sigma];
plot(x3, [0, 0], 'blue:', 'linewidth', 2);
fill([mu - 3*sigma, mu + 3*sigma], [0, 0], [], 'blue', 0.3);
text(mu - 3*sigma + 0.15, -0.1, "3σ", "fontsize", 14);

% 添加图例
legend('正态分布曲线', 'μ', '1σ', '2σ', '3σ', 'location', 'upper left');

hold off;

% 调整图形显示设置
set(gca, "box", "on");
set(gca, "grid", "on");
print("normal_distribution_plot.png", "-dpng", "-r600");

