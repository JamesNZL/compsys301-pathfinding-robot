%%% SensorAnalysis.m
% A MATLAB script to analyse the response of a sensor excited by a test circuit using the saved output from an oscilloscope.
%
% Author: James Bao

%% Sanitise workspace
clear;
close all;
clc;

fprintf("SensorAnalysis.m\n\n");

%% Script Configuration

% Sensor directory
SENSOR_DIR = 'phototransistor';

% The test case to import
FILE_NAME = 'off-white';

% The set of file suffixes for each test case
% * "fft-samples" can also be used, but, the "fft" file
% * actually contains *both* the raw samples and the scope's
% * fft data
% * the textscan() of "fft" will fail once it hits the header
% * rows at the top of the fft data, so treating it as a regular data
% * file will also work
FILE_SUFFIXES = ["10m", "1m", "fft"];
FILES_COUNT = length(FILE_SUFFIXES);

% The file suffix of the exported FFT data
FILE_FFT_SUFFIX = 'fft';

% The format of the CSV data
DATA_FORMAT = '%f,%f';

% The number of header rows in the output CSV data
LINES_TO_SKIP = 2;
LINES_TO_SKIP_FFT = LINES_TO_SKIP + 2002;

% The voltage scaling factor
VOLTAGE_SCALE = 1;

% The default upper FFT frequency view limit
FFT_UPPER_VIEW_LIMIT = 300;

%% Data Import

data = cell(1, FILES_COUNT);

for i = 1:FILES_COUNT
    % Construct the file name
    file_name = strcat(SENSOR_DIR, '/', FILE_NAME, '-', FILE_SUFFIXES(i), '.csv');
    
    % Load the CSV file
    fid = fopen(file_name);
    data{i} = textscan(fid, DATA_FORMAT, 'Headerlines', LINES_TO_SKIP);
    fclose(fid);
end

% Raw FFT file
file_name = strcat(SENSOR_DIR, '/', FILE_NAME, '-', FILE_FFT_SUFFIX, '.csv');

% Load the CSV file
fid = fopen(file_name);
raw_fft_data = textscan(fid, DATA_FORMAT, 'Headerlines', LINES_TO_SKIP_FFT);
fclose(fid);

%% Raw Plot

figure;
for i = 1:FILES_COUNT
    % Extract time and voltage data
    [time, voltage] = data{i}{1:2};
    
    % Sampling frequency, assuming equidistant time points
    Fs = 1 / mean(diff(time));
    
    subplot(FILES_COUNT, 1, i);
    plot(time * 1000, voltage * VOLTAGE_SCALE);
    xlabel('Time (ms)');
    ylabel('Voltage (V)');
    title(strcat(SENSOR_DIR, ": ", FILE_NAME, " @", num2str(Fs), "Hz"));
end

%% Calculate FFT

figure;
for i = 1:FILES_COUNT
    % Extract time and voltage data
    [time, voltage] = data{i}{1:2};
    
    L = length(voltage);
    
    % Sampling frequency, assuming equidistant time points
    Fs = 1 / mean(diff(time));
    f = Fs*(0:(L/2))/L;
    
    % Compute the FFT
    FFT = fft(voltage);
    FFT = abs(FFT ./ L);
    
    % Compute the one-sided amplitude spectrum
    one_sided_spectrum = FFT(1:L/2+1);
    one_sided_spectrum(2:end-1) = 2 .* one_sided_spectrum(2:end-1);
    
    % Plot the amplitude spectrum
    subplot((FILES_COUNT + 1), 1, i);
    plot(f, one_sided_spectrum);
    xlabel('Frequency (Hz)');
    xlim([0, FFT_UPPER_VIEW_LIMIT]);
    ylabel('Amplitude (V)');
	title(strcat(SENSOR_DIR, " FFT: ", FILE_NAME, " @", "", num2str(Fs), "Hz"));
end

subplot((FILES_COUNT + 1), 1, (FILES_COUNT + 1));
% A somewhat arbitrary scaling factor of 10 to try reconcile the y-axis
plot(raw_fft_data{1, 1}, 10*db2mag(raw_fft_data{1, 2}));
xlabel('Frequency (Hz)');
xlim([0, FFT_UPPER_VIEW_LIMIT]);
ylabel('Amplitude (V)');
title(strcat(SENSOR_DIR, " FFT: ", FILE_NAME, " @", "Oscilloscope FFT"));