% 清除所有变量和图形
clear; clf;

% 定义基站位置
bs1 = [0, 0]; % 基站1位置
bs2 = [10, 10]; % 基站2位置
bs3 = [20, 0]; % 基站3位置

% 定义距离差
d_diff_1_2 = 5; % UE到基站1比到基站2的距离大2
d_diff_1_3 = 8; % UE到基站1比到基站3的距离大4

% 时间同步误差导致的距离误差
sync_error = 0.5;

% 绘制无时间同步误差下的双曲线
hold on;
[x1, y1] = meshgrid(linspace(-10, 30, 400), linspace(-10, 20, 300));
z1 = sqrt((x1 - bs1(1)).^2 + (y1 - bs1(2)).^2) - sqrt((x1 - bs2(1)).^2 + (y1 - bs2(2)).^2) - d_diff_1_2;
contour(x1, y1, z1, [0, 0], 'r-', 'LineWidth', 2); % 红色实线表示无误差轨迹1-2
z2 = sqrt((x1 - bs1(1)).^2 + (y1 - bs1(2)).^2) - sqrt((x1 - bs3(1)).^2 + (y1 - bs3(2)).^2) - d_diff_1_3;
contour(x1, y1, z2, [0, 0], 'b-', 'LineWidth', 2); % 蓝色实线表示无误差轨迹1-3

% 绘制有时间同步误差下的双曲线
[x2, y2] = meshgrid(linspace(-10, 30, 400), linspace(-10, 20, 300));
z3 = sqrt((x2 - bs1(1)).^2 + (y2 - bs1(2)).^2) - sqrt((x2 - bs2(1)).^2 + (y2 - bs2(2)).^2) - d_diff_1_2 + sync_error;
contour(x2, y2, z3, [0, 0], 'r--', 'LineWidth', 2); % 红色虚线表示有误差轨迹1-2
z4 = sqrt((x2 - bs1(1)).^2 + (y2 - bs1(2)).^2) - sqrt((x2 - bs3(1)).^2 + (y2 - bs3(2)).^2) - d_diff_1_3 + sync_error;
contour(x2, y2, z4, [0, 0], 'b--', 'LineWidth', 2); % 蓝色虚线表示有误差轨迹1-3

% 绘制基站位置并使用不同颜色
plot(bs1(1), bs1(2), 'mo', 'MarkerSize', 10, 'MarkerFaceColor', 'm'); % 洋红色圆点表示基站1
text(bs1(1)+0.5, bs1(2), 'Radio 1', 'FontSize', 12, 'Color', 'm'); % 标签基站1
plot(bs2(1), bs2(2), 'co', 'MarkerSize', 10, 'MarkerFaceColor', 'c'); % 青色圆点表示基站2
text(bs2(1)+0.5, bs2(2), 'Radio 2', 'FontSize', 12, 'Color', 'c'); % 标签基站2
plot(bs3(1), bs3(2), 'yo', 'MarkerSize', 10, 'MarkerFaceColor', 'g'); % 黄色圆点表示基站3
text(bs3(1)+0.5, bs3(2), 'Radio 3', 'FontSize', 12, 'Color', 'g'); % 标签基站3

% 添加标签和标题
xlabel('X');
ylabel('Y');
title('UL-TDOA: Trajectories with Constant Difference in Distance to Three Base Stations (w/ vs. w/o Sync Error)');
legend('No Sync error 1-2', 'No Sync error 1-3', 'With Sync error 1-2', 'With Sync error 1-3');

% 设置图形比例相同
axis equal;


%{
重新写octave代码模拟以下要求：
1. 模拟三个base station，base station1位于[0,0], base station2位于[10,10], base station3位于[20,0]
2. 一个UE，到base station1比到base station2的距离大2，用红色实线画出这个UE所在的位置
3. 这个UE，到base station1比到base station3的距离大4，用蓝色实线画出这个UE所在的位置
4. 以下假如base station1, base station2, base station3之间时间同步有误差导致距离误差为0.5
5. 一个UE，到base station1比到base station2的距离大2，用红色虚线画出这个UE所在的位置
6. 这个UE，到base station1比到base station3的距离大4，用蓝色虚线画出这个UE所在的位置
7. 用不同的颜色标注基站
8. 所有的标注用英文
9. 计算实线和实线的交点位置并表示，计算虚线和虚线的交点位置并表示
%}
