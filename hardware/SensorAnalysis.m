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
FILE_SUFFIXES = ["10m", "1m", "fft-samples"];
FILES_COUNT = length(FILE_SUFFIXES);

% The file suffix of the exported FFT data
FILE_FFT_NAME = 'fft';

% The format of the CSV data
DATA_FORMAT = '%f,%f';

% The number of header rows in the output CSV data
LINES_TO_SKIP = 2;

% The voltage scaling factor
VOLTAGE_SCALE = 1;

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

%% Raw Plot

figure;
for i = 1:FILES_COUNT
	% Extract time and voltage data
	[time, voltage] = data{i}{1:2};
	
	subplot(FILES_COUNT, 1, i);
	plot(time * 1000, voltage * VOLTAGE_SCALE);
	xlabel('Time (ms)');
	ylabel('Voltage (V)');
	title(strcat(SENSOR_DIR, ": ", FILE_NAME, " @", FILE_SUFFIXES(i)));
end

%% TODO: Calculate FFT
