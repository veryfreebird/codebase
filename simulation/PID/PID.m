%% Step Adjustment vs Smooth Adjustment Comparison - Final Fixed Version
clear all; close all; clc;

% Helper function
function result = ternary_str(condition)
    if condition
        result = 'YES';
    else
        result = 'NO';
    end
end

% Simulation parameters
dt = 0.1;  % Sampling time 0.1 seconds
T = 20;    % Total time 20 seconds
t = 0:dt:T;
n = length(t);

% Scenario: Large initial offset
initial_offset = 5e6;  % 5ms = 5,000,000 ns

fprintf('Simulation Parameters:\n');
fprintf('Sampling time dt = %.2f seconds\n', dt);
fprintf('Total time T = %.0f seconds\n', T);
fprintf('Initial offset = %.0f ns (%.1f ms)\n', initial_offset, initial_offset/1e6);
fprintf('Number of points n = %d\n\n', n);

%% Method 1: Smooth adjustment only (PI control)
disp('=== Method 1: Smooth adjustment only ===');

offset_smooth = zeros(1, n);
freq_smooth = zeros(1, n);
offset_smooth(1) = initial_offset;
integral = 0;
Kp = 0.3;    % Proportional gain
Ki = 0.1;    % Integral gain
max_freq = 500000;  % Maximum frequency adjustment ±500,000ppb (500ppm)

fprintf('First 5 iterations:\n');
fprintf('i\tTime(s)\tOffset(ns)\tIntegral\tFreq(ppb)\tChange(ns)\tNewOffset(ns)\n');
fprintf('--------------------------------------------------------------------------------\n');

for i = 1:n-1
    % Current offset
    current_offset = offset_smooth(i);

    % PI control calculation
    proportional = Kp * current_offset;
    integral = integral + Ki * current_offset * dt;

    % Anti-windup
    if integral > max_freq
        integral = max_freq;
    elseif integral < -max_freq
        integral = -max_freq;
    end

    % Total frequency adjustment
    freq_adj = proportional + integral;

    % Limiter
    if freq_adj > max_freq
        freq_adj = max_freq;
    elseif freq_adj < -max_freq
        freq_adj = -max_freq;
    end

    freq_smooth(i) = freq_adj;

    % System dynamics: offset change = -frequency adjustment * time
    offset_change = freq_adj * dt;  % freq_adj(ppb) * dt(seconds) = change in ns

    offset_smooth(i+1) = current_offset - offset_change;

    if i <= 5
        fprintf('%d\t%.1f\t%.0f\t%.0f\t%.0f\t%.0f\t%.0f\n', ...
            i, t(i), current_offset, integral, freq_adj, offset_change, offset_smooth(i+1));
    end
end
freq_smooth(end) = freq_smooth(end-1);

%% Method 2: Step + Smooth adjustment
disp('=== Method 2: Step + Smooth adjustment ===');

offset_step = zeros(1, n);
freq_step = zeros(1, n);
offset_step(1) = initial_offset;
integral = 0;
step_threshold = 1e6;  % 1ms
step_applied = false;
step_time_idx = 0;

fprintf('\nFirst 5 iterations:\n');
fprintf('i\tTime(s)\tOffset(ns)\tFreq(ppb)\tChange(ns)\tNewOffset(ns)\tStepApplied\n');
fprintf('--------------------------------------------------------------------------------\n');

for i = 1:n-1
    current_offset = offset_step(i);
    step_info = 'No';

    % Check if step adjustment is needed
    if ~step_applied && abs(current_offset) > step_threshold
        % Apply step adjustment
        if current_offset > 0
            offset_step(i) = current_offset - step_threshold;
        else
            offset_step(i) = current_offset + step_threshold;
        end
        freq_step(i) = 0;
        integral = 0;  % Reset integrator
        step_applied = true;
        step_time_idx = i;
        step_info = 'Yes';

        current_offset = offset_step(i);  % Update after step
    else
        % PI control
        proportional = Kp * current_offset;
        integral = integral + Ki * current_offset * dt;

        % Anti-windup
        if integral > max_freq
            integral = max_freq;
        elseif integral < -max_freq
            integral = -max_freq;
        end

        freq_adj = proportional + integral;

        % Limiter
        if freq_adj > max_freq
            freq_adj = max_freq;
        elseif freq_adj < -max_freq
            freq_adj = -max_freq;
        end

        freq_step(i) = freq_adj;
    end

    % System dynamics
    offset_change = freq_step(i) * dt;
    offset_step(i+1) = offset_step(i) - offset_change;

    if i <= 5
        fprintf('%d\t%.1f\t%.0f\t%.0f\t%.0f\t%.0f\t%s\n', ...
            i, t(i), current_offset, freq_step(i), offset_change, offset_step(i+1), step_info);
    end
end
freq_step(end) = freq_step(end-1);

%% Performance Analysis
fprintf('\n=============== Performance Analysis ===============\n');

% Calculate settling times
settling_threshold = 1000;  % 1us
settling_time_smooth = T;
settling_time_step = T;
idx_smooth = find(abs(offset_smooth) < settling_threshold, 1);
idx_step = find(abs(offset_step) < settling_threshold, 1);

if ~isempty(idx_smooth)
    settling_time_smooth = t(idx_smooth);
    fprintf('Smooth adjustment only:\n');
    fprintf('  Time to 1μs: %.2f seconds\n', settling_time_smooth);
    fprintf('  Final offset: %.0f ns (%.3f ms)\n', offset_smooth(end), offset_smooth(end)/1e6);
    fprintf('  Max frequency adjustment: %.0f ppb (%.0f ppm)\n', ...
        max(abs(freq_smooth)), max(abs(freq_smooth))/1000);
else
    fprintf('Smooth adjustment only: Did not settle to 1μs within %d seconds\n', T);
end

fprintf('\n');

if ~isempty(idx_step)
    settling_time_step = t(idx_step);
    fprintf('Step + Smooth adjustment:\n');
    if step_applied
        fprintf('  Step adjustment: %.1f ms\n', step_threshold/1e6);
    end
    fprintf('  Time to 1μs: %.2f seconds\n', settling_time_step);
    fprintf('  Final offset: %.0f ns (%.3f ms)\n', offset_step(end), offset_step(end)/1e6);
    fprintf('  Max frequency adjustment: %.0f ppb (%.0f ppm)\n', ...
        max(abs(freq_step)), max(abs(freq_step))/1000);
else
    fprintf('Step + Smooth adjustment: Did not settle to 1μs within %d seconds\n', T);
end

fprintf('\nPerformance comparison:\n');
if settling_time_smooth < T && settling_time_step < T
    fprintf('  Step adjustment speedup: %.1f times\n', settling_time_smooth/settling_time_step);
    fprintf('  Time reduction: %.1f seconds\n', settling_time_smooth - settling_time_step);
else
    fprintf('  Note: At least one method did not settle\n');
end
fprintf('===================================================\n');

%% MAIN COMPARISON PLOT
figure('Position', [50, 50, 1400, 900], 'Name', 'Step vs Smooth Adjustment Comparison');

% Subplot 1: Smooth adjustment only
subplot(2, 2, 1);
plot(t, offset_smooth / 1e6, 'b-', 'LineWidth', 2);
hold on;
% Draw horizontal line for threshold
threshold_y = 0.001 * ones(1, 2);
threshold_x = [0, T];
plot(threshold_x, threshold_y, 'k--', 'LineWidth', 1.5, 'DisplayName', '1ms threshold');
grid on;
xlabel('Time (s)', 'FontSize', 12);
ylabel('Clock Offset (ms)', 'FontSize', 12);
title('Smooth Adjustment Only (PI Control)', 'FontSize', 14, 'FontWeight', 'bold');

% Auto-adjust y-axis
y_min = min(offset_smooth) / 1e6;
y_max = max(offset_smooth) / 1e6;
y_padding = (y_max - y_min) * 0.1;
if y_padding == 0
    y_padding = 0.5;
end
ylim([y_min - y_padding, y_max + y_padding]);

legend('Clock Offset', 'Step Threshold', 'Location', 'northeast');

% Mark settling time
if ~isempty(idx_smooth)
    plot(t(idx_smooth), offset_smooth(idx_smooth)/1e6, 'b^', ...
        'MarkerSize', 12, 'LineWidth', 2, 'MarkerFaceColor', 'b');
    text(t(idx_smooth)+0.3, offset_smooth(idx_smooth)/1e6 + 0.3, ...
        sprintf('Settled: %.1fs', t(idx_smooth)), 'Color', 'b', 'FontSize', 11);
end

% Subplot 2: Step + Smooth adjustment
subplot(2, 2, 2);
plot(t, offset_step / 1e6, 'r-', 'LineWidth', 2);
hold on;
% Draw horizontal line for threshold
plot(threshold_x, threshold_y, 'k--', 'LineWidth', 1.5, 'DisplayName', '1ms threshold');

% Mark step adjustment point
if step_applied && step_time_idx > 0
    plot(t(step_time_idx), offset_step(step_time_idx)/1e6, 'ro', ...
        'MarkerSize', 12, 'LineWidth', 2, 'MarkerFaceColor', 'r');
    text(t(step_time_idx)+0.3, offset_step(step_time_idx)/1e6 + 0.3, ...
        sprintf('Step: -%.1fms', step_threshold/1e6), 'Color', 'r', 'FontSize', 11);
end

grid on;
xlabel('Time (s)', 'FontSize', 12);
ylabel('Clock Offset (ms)', 'FontSize', 12);
title('Step + Smooth Adjustment', 'FontSize', 14, 'FontWeight', 'bold');

% Auto-adjust y-axis
y_min = min(offset_step) / 1e6;
y_max = max(offset_step) / 1e6;
y_padding = (y_max - y_min) * 0.1;
if y_padding == 0
    y_padding = 0.5;
end
ylim([y_min - y_padding, y_max + y_padding]);

if step_applied
    legend('Clock Offset', 'Step Threshold', 'Step Point', 'Location', 'northeast');
else
    legend('Clock Offset', 'Step Threshold', 'Location', 'northeast');
end

% Mark settling time
if ~isempty(idx_step)
    plot(t(idx_step), offset_step(idx_step)/1e6, 'r^', ...
        'MarkerSize', 12, 'LineWidth', 2, 'MarkerFaceColor', 'r');
    text(t(idx_step)+0.3, offset_step(idx_step)/1e6 - 0.3, ...
        sprintf('Settled: %.1fs', t(idx_step)), 'Color', 'r', 'FontSize', 11);
end

% Subplot 3: Frequency adjustment comparison
subplot(2, 2, 3);
plot(t, freq_smooth / 1000, 'b-', 'LineWidth', 1.5);
hold on;
plot(t, freq_step / 1000, 'r-', 'LineWidth', 1.5);

% Draw horizontal lines for limits
limit_y_upper = (max_freq/1000) * ones(1, 2);
limit_y_lower = (-max_freq/1000) * ones(1, 2);
plot(threshold_x, limit_y_upper, 'g--', 'LineWidth', 1.5, ...
     'DisplayName', sprintf('Upper: %d ppm', max_freq/1000));
plot(threshold_x, limit_y_lower, 'g--', 'LineWidth', 1.5, ...
     'DisplayName', sprintf('Lower: -%d ppm', max_freq/1000));

grid on;
xlabel('Time (s)', 'FontSize', 12);
ylabel('Frequency Adjustment (ppm)', 'FontSize', 12);
title('Frequency Adjustment Comparison', 'FontSize', 14, 'FontWeight', 'bold');

% Auto-adjust y-axis for frequency
freq_min = min(min(freq_smooth/1000), min(freq_step/1000));
freq_max = max(max(freq_smooth/1000), max(freq_step/1000));
freq_padding = (freq_max - freq_min) * 0.1;
if freq_padding == 0
    freq_padding = 50;
end
ylim([freq_min - freq_padding, freq_max + freq_padding]);

legend('Smooth Only', 'Step+Smooth', 'Location', 'northeast');

% Subplot 4: Settling process comparison (log scale)
subplot(2, 2, 4);
% Use absolute values for log plot
abs_offset_smooth = abs(offset_smooth);
abs_offset_smooth(abs_offset_smooth == 0) = 1e-9;  % Avoid log(0)
abs_offset_step = abs(offset_step);
abs_offset_step(abs_offset_step == 0) = 1e-9;  % Avoid log(0)

semilogy(t, abs_offset_smooth / 1e3, 'b-', 'LineWidth', 2, 'DisplayName', 'Smooth Only');
hold on;
semilogy(t, abs_offset_step / 1e3, 'r-', 'LineWidth', 2, 'DisplayName', 'Step+Smooth');

% Draw horizontal line for settling threshold
settling_line_y = 1 * ones(1, 2);
plot(threshold_x, settling_line_y, 'k-', 'LineWidth', 2, ...
     'DisplayName', '1μs Settling Threshold');

grid on;
xlabel('Time (s)', 'FontSize', 12);
ylabel('|Clock Offset| (μs)', 'FontSize', 12);
title('Settling Process Comparison (Log Scale)', 'FontSize', 14, 'FontWeight', 'bold');

% Auto-adjust y-axis for log plot
log_min = min(min(abs_offset_smooth/1e3), min(abs_offset_step/1e3));
log_max = max(max(abs_offset_smooth/1e3), max(abs_offset_step/1e3));
if log_min > 0 && log_max > 0
    ylim([log_min/10, log_max*10]);
end

legend('Location', 'northeast');
xlim([0, T]);

%% DETAILED CONVERGENCE ANALYSIS
figure('Position', [100, 100, 1200, 600], 'Name', 'Detailed Convergence Analysis');

% Subplot 1: Full convergence process
subplot(1, 2, 1);
plot(t, offset_smooth / 1e6, 'b-', 'LineWidth', 2, 'DisplayName', 'Smooth Only');
hold on;
plot(t, offset_step / 1e6, 'r-', 'LineWidth', 2, 'DisplayName', 'Step+Smooth');
plot([0, T], [0, 0], 'k:', 'LineWidth', 1, 'DisplayName', 'Zero');
plot([0, T], [0.001, 0.001], 'k--', 'LineWidth', 1, 'DisplayName', '1ms threshold');
grid on;
xlabel('Time (s)', 'FontSize', 12);
ylabel('Clock Offset (ms)', 'FontSize', 12);
title('Full Convergence Process', 'FontSize', 14, 'FontWeight', 'bold');

% Auto-adjust y-axis
y_min = min(min(offset_smooth/1e6), min(offset_step/1e6));
y_max = max(max(offset_smooth/1e6), max(offset_step/1e6));
y_padding = (y_max - y_min) * 0.1;
if y_padding == 0
    y_padding = 0.5;
end
ylim([y_min - y_padding, y_max + y_padding]);

legend('Location', 'northeast');

% Mark important points
if step_applied && step_time_idx > 0
    plot(t(step_time_idx), offset_step(step_time_idx)/1e6, 'ro', ...
        'MarkerSize', 10, 'LineWidth', 2, 'MarkerFaceColor', 'r');
end

% Subplot 2: Convergence rate analysis
subplot(1, 2, 2);
% Calculate convergence rate
convergence_rate_smooth = zeros(1, n-1);
convergence_rate_step = zeros(1, n-1);

for i = 1:n-1
    if i < n
        convergence_rate_smooth(i) = (abs(offset_smooth(i)) - abs(offset_smooth(i+1))) / dt;
        convergence_rate_step(i) = (abs(offset_step(i)) - abs(offset_step(i+1))) / dt;
    end
end

plot(t(1:end-1), convergence_rate_smooth / 1e6, 'b-', 'LineWidth', 2, 'DisplayName', 'Smooth Only');
hold on;
plot(t(1:end-1), convergence_rate_step / 1e6, 'r-', 'LineWidth', 2, 'DisplayName', 'Step+Smooth');
grid on;
xlabel('Time (s)', 'FontSize', 12);
ylabel('Convergence Rate (ms/s)', 'FontSize', 12);
title('Instantaneous Convergence Rate', 'FontSize', 14, 'FontWeight', 'bold');

% Auto-adjust y-axis for convergence rate
rate_min = min(min(convergence_rate_smooth/1e6), min(convergence_rate_step/1e6));
rate_max = max(max(convergence_rate_smooth/1e6), max(convergence_rate_step/1e6));
rate_padding = (rate_max - rate_min) * 0.1;
if rate_padding == 0
    rate_padding = 0.1;
end
ylim([rate_min - rate_padding, rate_max + rate_padding]);

legend('Location', 'northeast');

%% PARAMETER SENSITIVITY ANALYSIS
fprintf('\n=============== Parameter Sensitivity Analysis ===============\n');

% Test different parameter sets
param_sets = [
    0.1, 0.05;   % Conservative
    0.3, 0.1;    % Current
    0.5, 0.2;    % Aggressive
    0.7, 0.3;    % Very aggressive
];

% Create figure for parameter sensitivity
figure('Position', [100, 100, 1200, 800], 'Name', 'Parameter Sensitivity Analysis');

settling_times = zeros(size(param_sets, 1), 1);
final_offsets = zeros(size(param_sets, 1), 1);

for p = 1:size(param_sets, 1)
    Kp_test = param_sets(p, 1);
    Ki_test = param_sets(p, 2);

    % Simulate with these parameters
    offset_test = zeros(1, n);
    offset_test(1) = initial_offset;
    integral_test = 0;

    for i = 1:n-1
        proportional = Kp_test * offset_test(i);
        integral_test = integral_test + Ki_test * offset_test(i) * dt;

        % Anti-windup
        if integral_test > max_freq
            integral_test = max_freq;
        elseif integral_test < -max_freq
            integral_test = -max_freq;
        end

        freq_adj = proportional + integral_test;

        % Limiter
        if freq_adj > max_freq
            freq_adj = max_freq;
        elseif freq_adj < -max_freq
            freq_adj = -max_freq;
        end

        offset_test(i+1) = offset_test(i) - freq_adj * dt;
    end

    % Calculate performance metrics
    settling_idx = find(abs(offset_test) < settling_threshold, 1);
    if ~isempty(settling_idx)
        settling_times(p) = t(settling_idx);
    else
        settling_times(p) = T;
    end
    final_offsets(p) = offset_test(end);

    % Plot
    subplot(2, 2, p);
    plot(t, offset_test / 1e6, 'LineWidth', 2, 'Color', [p/4, 0.5, 1-p/4]);
    hold on;
    plot([0, T], [0.001, 0.001], 'k--', 'LineWidth', 1);
    grid on;
    xlabel('Time (s)');
    ylabel('Offset (ms)');
    title(sprintf('Kp=%.1f, Ki=%.2f', Kp_test, Ki_test));

    % Auto-adjust y-axis
    y_min_test = min(offset_test) / 1e6;
    y_max_test = max(offset_test) / 1e6;
    y_padding_test = (y_max_test - y_min_test) * 0.1;
    if y_padding_test == 0
        y_padding_test = 0.5;
    end
    ylim([y_min_test - y_padding_test, y_max_test + y_padding_test]);

    if settling_times(p) < T
        text(2, y_max_test*0.8, sprintf('Settle: %.1fs', settling_times(p)), ...
             'BackgroundColor', 'white', 'FontSize', 10);
    end

    fprintf('Kp=%.1f, Ki=%.2f: Settling time=%.1fs, Final offset=%.0fns\n', ...
        Kp_test, Ki_test, settling_times(p), final_offsets(p));
end
fprintf('===========================================================\n');

%% CONVERGENCE SUMMARY PLOT
figure('Position', [100, 100, 1000, 800], 'Name', 'Convergence Summary');

% Calculate bar heights and positions
methods = {'Smooth', 'Step+Smooth'};
final_errors = [abs(offset_smooth(end)), abs(offset_step(end))] / 1e3;  % in μs
settling_times_plot = [settling_time_smooth, settling_time_step];
max_freqs = [max(abs(freq_smooth)), max(abs(freq_step))] / 1000;  % in ppm

% Find maximum values for consistent scaling
max_final_error = max(final_errors);
max_settling_time = max(settling_times_plot);
max_freq = max(max_freqs);

% Ensure minimum values for bar plot visibility
if max_final_error == 0
    max_final_error = 0.1;
end
if max_settling_time == 0
    max_settling_time = 1;
end
if max_freq == 0
    max_freq = 10;
end

% Subplot 1: Final error comparison
subplot(2, 2, 1);
bar(1:2, final_errors, 0.6, 'FaceColor', [0.2, 0.6, 0.8]);
set(gca, 'XTickLabel', methods, 'XTick', 1:2);
ylabel('Final Error (μs)');
title('Final Error Comparison', 'FontSize', 12, 'FontWeight', 'bold');
grid on;
% Add value labels
for i = 1:2
    text(i, final_errors(i) + max_final_error*0.05, ...
         sprintf('%.1f', final_errors(i)), ...
         'HorizontalAlignment', 'center', 'FontWeight', 'bold', 'FontSize', 10);
end
% Set y-axis limit
ylim([0, max_final_error * 1.2]);

% Subplot 2: Settling time comparison
subplot(2, 2, 2);
bar(1:2, settling_times_plot, 0.6, 'FaceColor', [0.8, 0.4, 0.4]);
set(gca, 'XTickLabel', methods, 'XTick', 1:2);
ylabel('Settling Time to 1μs (s)');
title('Settling Time Comparison', 'FontSize', 12, 'FontWeight', 'bold');
grid on;
% Add value labels
for i = 1:2
    text(i, settling_times_plot(i) + max_settling_time*0.05, ...
         sprintf('%.1f', settling_times_plot(i)), ...
         'HorizontalAlignment', 'center', 'FontWeight', 'bold', 'FontSize', 10);
end
% Set y-axis limit
ylim([0, max_settling_time * 1.2]);

% Subplot 3: Max frequency used
subplot(2, 2, 3);
bar(1:2, max_freqs, 0.6, 'FaceColor', [0.4, 0.8, 0.4]);
set(gca, 'XTickLabel', methods, 'XTick', 1:2);
ylabel('Max Frequency Adjustment (ppm)');
title('Maximum Frequency Used', 'FontSize', 12, 'FontWeight', 'bold');
grid on;
% Add value labels
for i = 1:2
    text(i, max_freqs(i) + max_freq*0.05, ...
         sprintf('%.0f', max_freqs(i)), ...
         'HorizontalAlignment', 'center', 'FontWeight', 'bold', 'FontSize', 10);
end
% Set y-axis limit
ylim([0, max_freq * 1.2]);

% Subplot 4: Performance summary
subplot(2, 2, 4);
axis off;
summary_text = sprintf(['Performance Summary:\n\n' ...
                       'Smooth Adjustment Only:\n' ...
                       '  Settling time: %.1f s\n' ...
                       '  Final error: %.0f ns\n' ...
                       '  Max freq: %.0f ppm\n\n' ...
                       'Step + Smooth:\n' ...
                       '  Settling time: %.1f s\n' ...
                       '  Final error: %.0f ns\n' ...
                       '  Max freq: %.0f ppm\n\n' ...
                       'Speedup: %.1fx'], ...
                       settling_time_smooth, offset_smooth(end), max(abs(freq_smooth))/1000, ...
                       settling_time_step, offset_step(end), max(abs(freq_step))/1000, ...
                       settling_time_smooth/settling_time_step);
text(0.1, 0.5, summary_text, 'FontSize', 10, 'VerticalAlignment', 'middle', 'FontName', 'Monospaced');

%% Final convergence test
fprintf('\n=============== Final Convergence Test ===============\n');

% Test if system converges to near zero
final_offset_threshold = 100;  % 100ns
converged_smooth = abs(offset_smooth(end)) < final_offset_threshold;
converged_step = abs(offset_step(end)) < final_offset_threshold;

fprintf('Convergence to < 100ns:\n');
fprintf('  Smooth adjustment: %s (final offset: %.0f ns)\n', ...
    ternary_str(converged_smooth), offset_smooth(end));
fprintf('  Step + Smooth: %s (final offset: %.0f ns)\n', ...
    ternary_str(converged_step), offset_step(end));

% Calculate steady-state error
fprintf('\nSteady-state performance (last 10%% of simulation):\n');
last_10_percent = round(0.1 * n);
if last_10_percent > 0
    steady_state_smooth = mean(offset_smooth(end-last_10_percent+1:end));
    steady_state_step = mean(offset_step(end-last_10_percent+1:end));
    fprintf('  Smooth adjustment: %.0f ns\n', steady_state_smooth);
    fprintf('  Step + Smooth: %.0f ns\n', steady_state_step);
end
fprintf('==================================================\n');

%% Create a simple demonstration of the concept
fprintf('\n=============== Step Adjustment Concept ===============\n');
fprintf('Without step adjustment:\n');
fprintf('  Start at 5.0 ms offset\n');
fprintf('  Use only PI control (smooth adjustment)\n');
fprintf('  Takes about %.1f seconds to reach 1μs\n\n', settling_time_smooth);

fprintf('With step adjustment:\n');
fprintf('  Start at 5.0 ms offset\n');
fprintf('  First: Step adjustment of -1.0 ms\n');
fprintf('  Then: PI control from 4.0 ms offset\n');
fprintf('  Takes about %.1f seconds to reach 1μs\n\n', settling_time_step);

fprintf('Conclusion: Step adjustment reduces settling time by %.1f times\n', ...
    settling_time_smooth/settling_time_step);
fprintf('=====================================================\n');
