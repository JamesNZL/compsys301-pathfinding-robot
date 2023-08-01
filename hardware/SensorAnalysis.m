%%% SensorAnalysis.m
% A MATLAB script to analyse the response of a sensor excited by a test circuit using the saved output from an oscilloscope.
%
% ! To use this script:
% * Create a sibling directory for each sensor type, and add it to SENSOR_DIR_NAMES
% * Name each exported CSV file in the format [room light state]-[projector test condition]-[suffix].csv
% * Where:
% * 	- [room light state] corresponds to an entry in FILE_PREFIXES
% * 	- [projector test condition] corresponds to an entry in FILE_NAMES
% * 	- [suffix] corresponds to a suffix in FILE_SUFFIXES
%
% Author: James Bao

%% Sanitise workspace
clear;
close all;
clc;

fprintf("SensorAnalysis.m\n\n");

%% Script Configuration

% Sensor directory
SENSOR_DIR_NAMES = ["phototransistor"];

% The set of file prefixes for each test case,
% corresponding to the state of the room light
FILE_PREFIXES = ["on"]; # "off"

% The various projector test conditions
FILE_NAMES = ["black", "green", "white"];

% The set of file suffixes for each test case
% * "fft-samples" can also be used, but, the "fft" file
% * actually contains *both* the raw samples and the scope's
% * fft data
% * the textscan() of "fft" will fail once it hits the header
% * rows at the top of the fft data, so treating it as a regular data
% * file will also work
FILE_SUFFIXES = ["2ms", "20ms", "200ms", "2s", "5s"];

% The file suffix of the exported FFT data
FILE_FFT_SUFFIX = 'fft';

% The format of the CSV data
DATA_FORMAT = '%f,%f';

% The number of header rows in the output CSV data
LINES_TO_SKIP = 1;
LINES_TO_SKIP_FFT = LINES_TO_SKIP + 2003;

% The voltage scaling factor
VOLTAGE_SCALE = 1;

% The default upper voltage view limit
VOLTAGE_UPPER_VIEW_LIMIT = 5;

% The default upper FFT frequency view limit
FFT_UPPER_VIEW_LIMIT = 300;

%% Data Import

SENSOR_COUNT = length(SENSOR_DIR_NAMES);
PREFIX_COUNT = length(FILE_PREFIXES);
TEST_COUNT = length(FILE_NAMES);
SUFFIX_COUNT = length(FILE_SUFFIXES);

% This is a 4D cell array, where
% dimension 1: the sensor type
% dimension 2: whether the room light is on
% dimension 3: the projector test condition (green, white, black)
% dimension 4: the various sampling rates for each condition (and the raw fft data)
data = cell(PREFIX_COUNT, TEST_COUNT, SUFFIX_COUNT + 1);

for l = 1:SENSOR_COUNT
	for i = 1:PREFIX_COUNT
		for j = 1:TEST_COUNT
			for k = 1:SUFFIX_COUNT
				% Construct the file name
				file_name = strcat(SENSOR_DIR_NAMES(l), '/', FILE_PREFIXES(i), '-', FILE_NAMES(j), '-', FILE_SUFFIXES(k), '.csv');
				
				% Load the CSV file
				fid = fopen(file_name);
				data{l, i, j, k} = textscan(fid, DATA_FORMAT, 'Headerlines', LINES_TO_SKIP);
				fclose(fid);
			end
			
			% Raw FFT file
			file_name = strcat(SENSOR_DIR_NAMES(l), '/', FILE_PREFIXES(i), '-', FILE_NAMES(j), '-', FILE_FFT_SUFFIX, '.csv');
			
			% Load the CSV file
			fid = fopen(file_name);
			data{l, i, j, (SUFFIX_COUNT + 1)} = textscan(fid, DATA_FORMAT, 'Headerlines', LINES_TO_SKIP_FFT);
			fclose(fid);
		end
	end
end

%% Raw Plot

for l = 1:SENSOR_COUNT
	for i = 1:PREFIX_COUNT
		figure('Name', strcat(SENSOR_DIR_NAMES(l), " lights ", FILE_PREFIXES(i)));
		
		for j = 1:TEST_COUNT
			for k = 1:SUFFIX_COUNT
				% Extract time and voltage data
				[time, voltage] = data{l, i, j, k}{1:2};
				
				% Sampling frequency, assuming equidistant time points
				Fs = 1 / mean(diff(time));
				
				subplot(SUFFIX_COUNT, TEST_COUNT, (3*(k-1) + (j)));
				plot(time * 1000, voltage * VOLTAGE_SCALE);
				xlabel('Time (ms)');
				ylabel('Voltage (V)');
				ylim([0, VOLTAGE_UPPER_VIEW_LIMIT]);
				title(strcat(SENSOR_DIR_NAMES(l), " (lights ", FILE_PREFIXES(i), "): ", FILE_NAMES(j), " @", num2str(Fs), "Hz"));
			end
		end
	end
end

%% Calculate FFT

for l = 1:SENSOR_COUNT
	for i = 1:PREFIX_COUNT
		figure('Name', strcat(SENSOR_DIR_NAMES(l), " lights ", FILE_PREFIXES(i), " FFT"));
		
		for j = 1:TEST_COUNT
			for k = 1:SUFFIX_COUNT
				% Extract time and voltage data
				[time, voltage] = data{l, i, j, k}{1:2};
				
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
				
				% Convert to dBV
				one_sided_spectrum = mag2db(one_sided_spectrum);
				
				% Plot the amplitude spectrum
				subplot((SUFFIX_COUNT + 1), TEST_COUNT, (3*(k-1) + (j)));
				plot(f, one_sided_spectrum);
				xlabel('Frequency (Hz)');
				xlim([0, FFT_UPPER_VIEW_LIMIT]);
				ylabel('Amplitude (V)');
				title(strcat(SENSOR_DIR_NAMES(l), " (lights ", FILE_PREFIXES(i), ") FFT: ", FILE_NAMES(j), " @", "", num2str(Fs), "Hz"));
			end
			
			subplot((SUFFIX_COUNT + 1), TEST_COUNT, (3*(SUFFIX_COUNT) + (j)));
			plot(data{l, i, j, (SUFFIX_COUNT + 1)}{1, 1}, data{l, i, j, (SUFFIX_COUNT + 1)}{1, 2});
			xlabel('Frequency (Hz)');
			xlim([0, FFT_UPPER_VIEW_LIMIT]);
			ylabel('Amplitude (V)');
			title(strcat(SENSOR_DIR_NAMES(l), " (lights ", FILE_PREFIXES(i), ") FFT: ", FILE_NAMES(j), " @", "Oscilloscope FFT"));
		end
	end
end