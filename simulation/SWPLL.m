clc;
clear all;

% 仿真数据长度
SimLens = 1000;

% 载波信号
Fs = 2400;
Ts = 1 / Fs;

Fsig = 60;

% 随机初相
Delta_Phase = rand(1)*2*pi;

SignalMod = exp(-1i*(Fsig/Fs * (1: SimLens) + Delta_Phase));

% 锁相环处理过程
Signal_PLL = zeros(SimLens, 1);
NCO_Phase = zeros(SimLens, 1);
nco = zeros(SimLens, 1);
Discriminator_Out = zeros(SimLens, 1);
Freq_Control = zeros(SimLens, 1);
PLL_Phase_Part = zeros(SimLens, 1);
PLL_Freq_Part = zeros(SimLens, 1);

% 环路参数
C1 = 0.012013;
C2 = 0.000247;

% 正交鉴相器
for i = 2 : SimLens
    Signal_PLL(i) = SignalMod(i) * exp(-1i * NCO_Phase(i-1));
    I_PLL(i) = real(Signal_PLL(i));
    Q_PLL(i) = imag(Signal_PLL(i));

    Discriminator_Out(i) = atan2(Q_PLL(i), I_PLL(i));

    PLL_Phase_Part(i) = Discriminator_Out(i) * C1;
    Freq_Control(i) = PLL_Phase_Part(i) + PLL_Freq_Part(i-1);

    NCO_Phase(i) = NCO_Phase(i-1) + Freq_Control(i);
    PLL_Freq_Part(i) = Discriminator_Out(i) * C2 + PLL_Freq_Part(i-1);
end

nco = cos(NCO_Phase);

figure;
plot(real(SignalMod), 'r+');
hold on;
plot(nco, 'b*');
hold on;
grid on;

figure
subplot(2,1,1)
plot(-PLL_Freq_Part(2: SimLens)*Fs);
grid on;
title('PLL频率响应曲线图');
axis([1 SimLens -100 100]);
subplot(2,1,2)
plot(PLL_Phase_Part(2: SimLens)*180/pi);
title('PLL相位响应曲线图');
axis([1 SimLens -2 2]);
grid on;

