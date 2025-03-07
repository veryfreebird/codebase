%% GPS四卫星定位与时间校正程序
% 作者：基于CSDN技术文档实现
% 功能：通过四颗卫星伪距观测值，解算接收机三维坐标和钟差

%% 初始化参数
clc; clear all;

% 真实接收机参数（未知待求解）
true_pos = [3e6; 2e6; 4e6];   % ECEF坐标系下的真实坐标（单位：米）
true_dt = 1e-6;               % 接收机钟差（秒）

% 模拟四颗卫星的ECEF坐标（基于地球静止轨道简化模型）
sat_pos = [
    2.6e7, 0, 0;            % 卫星1：赤道平面静止轨道
    0, 2.6e7, 0;            % 卫星2：赤道平面静止轨道
    0, 0, 2.6e7;            % 卫星3：极地轨道
    1.5e7, 1.5e7, 1.5e7     % 卫星4：倾斜轨道
];

% 物理常数
c = 299792458;              % 光速（米/秒）
noise_level = 5;            % 伪距测量噪声标准差（米）

%% 生成带噪声的伪距观测值
% 理论几何距离计算（无钟差和噪声）
geo_dist = sqrt(sum((sat_pos - true_pos').^2, 2));  % 每个卫星到接收机的几何距离

% 添加钟差影响和测量噪声
noise = noise_level * randn(4,1);            % 高斯白噪声
pseudo_ranges = geo_dist + c * true_dt + noise;  % 伪距=几何距离+钟差+噪声

%% 迭代最小二乘法解算
% 初始猜测值（通常设为地球质心或前次定位结果）
est_pos = [0; 0; 0];       % 初始位置估计
est_dt = 0;                % 初始钟差估计
max_iter = 20;             % 最大迭代次数
epsilon = 1e-3;            % 收敛阈值（位置变化小于1毫米）

for iter = 1:max_iter
    % 计算估计伪距（几何距离 + 钟差影响）
    est_dist = sqrt(sum((sat_pos - est_pos').^2, 2)) + c * est_dt;

    % 构造雅可比矩阵H（几何矩阵）
    % H矩阵结构：[视线方向单位矢量, 1]（每行对应一颗卫星）
    H = [(sat_pos - est_pos') ./ est_dist, ones(4,1)];

    % 计算残差向量（观测伪距 - 估计伪距）
    delta_z = pseudo_ranges - est_dist;

    % 最小二乘法求解增量：Δx = (H^T H)^-1 H^T Δz
    delta_x = (H' * H) \ (H' * delta_z);

    % 更新估计值（位置和钟差）
    est_pos = est_pos + delta_x(1:3);          % 位置更新
    est_dt = est_dt + delta_x(4)/c;            % 钟差更新（将距离误差转换为时间误差）

    % 判断收敛条件（位置变化小于阈值）
    if norm(delta_x(1:3)) < epsilon
        fprintf('迭代收敛于第%d次\n', iter);
        break;
    end
end

%% 结果输出与误差分析
fprintf('\n===== 定位结果 =====\n');
fprintf('真实位置: [%.2f, %.2f, %.2f] 米\n', true_pos);
fprintf('解算位置: [%.2f, %.2f, %.2f] 米\n', est_pos);
fprintf('位置误差: %.2f 米\n', norm(true_pos - est_pos));
fprintf('钟差解算值: %.3e 秒\n', est_dt);
fprintf('钟差真实值: %.3e 秒\n', true_dt);
fprintf('钟差误差: %.3e 秒\n', abs(est_dt - true_dt));

%% 可视化卫星分布（可选）
% 在结果输出后添加卫星位置绘制
figure;
plot3(sat_pos(:,1), sat_pos(:,2), sat_pos(:,3), '^r', 'MarkerSize', 12); % 绘制卫星位置（红色三角）
hold on;
plot3(est_pos(1), est_pos(2), est_pos(3), 'bo', 'MarkerSize', 10);       % 绘制解算位置（蓝色圆点）
xlabel('X (米)'); ylabel('Y (米)'); zlabel('Z (米)');
title('卫星与接收机位置');
grid on;
axis equal;
legend('卫星', '接收机');

% 调整坐标轴范围（例如仅显示接收机附近的局部区域）
axis([est_pos(1)-1e6, est_pos(1)+1e6, ...
      est_pos(2)-1e6, est_pos(2)+1e6, ...
      est_pos(3)-1e6, est_pos(3)+1e6]);


