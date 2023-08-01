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

% Whether to plot the raw responses
PLOT_RAW_RESPONSES = true;

% Whether to plot the FFT responses
PLOT_FFT = true;

% Sensor directory
SENSOR_DIR_NAMES = ["phototransistor", "photodiode"];

% The upper voltage view limit for each sensor
VOLTAGE_UPPER_VIEW_LIMIT = [2, 0.8];

% The set of file prefixes for each test case,
% corresponding to the state of the room light
FILE_PREFIXES = ["on", "off"];

% The various projector test conditions
FILE_NAMES = ["none", "black", "green", "white"];

% The set of file suffixes for each test case
FILE_SUFFIXES = ["2ms", "20ms", "200ms", "2s", "5s"];

% Whether to plot the raw response for each file suffix
% * NOTE: PLOT_RAW_RESPONSES takes priority over these flags
PLOT_RAW_SUFFIXES = [true, true, true, true, true];

% Whether to plot the FFT response for each file suffix
% * NOTE: PLOT_FFT takes priority over these flags
PLOT_FFT_SUFFIXES = [true, true, true, true, true];

%{
 % The file suffix of the exported FFT data
FILE_FFT_SUFFIX = 'fft';
%}

% The format of the CSV data
DATA_FORMAT = '%f,%f';

% The number of header rows in the output CSV data
LINES_TO_SKIP = 1;
LINES_TO_SKIP_FFT = LINES_TO_SKIP + 2003;

% The voltage scaling factor
VOLTAGE_SCALE = 1;

% The default upper FFT frequency view limit
FFT_UPPER_VIEW_LIMIT = 300/2;

% Whether to discard FFT data above (4 * FFT_UPPER_VIEW_LIMIT) to improve performance
FFT_DISCARD_HIGH_FREQUENCY = true;

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
data = cell(SENSOR_COUNT, PREFIX_COUNT, TEST_COUNT, SUFFIX_COUNT);

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
				
				clear file_name fid;
			end
			
			%{
 			% Raw FFT file
			file_name = strcat(SENSOR_DIR_NAMES(l), '/', FILE_PREFIXES(i), '-', FILE_NAMES(j), '-', FILE_FFT_SUFFIX, '.csv');
			
			% Load the CSV file
			fid = fopen(file_name);
			data{l, i, j, (SUFFIX_COUNT + 1)} = textscan(fid, DATA_FORMAT, 'Headerlines', LINES_TO_SKIP_FFT);
			fclose(fid);

			clear file_name fid;
			%}
		end
	end
end

%% Raw Plot

if PLOT_RAW_RESPONSES
	for l = 1:SENSOR_COUNT
		figure('Name', SENSOR_DIR_NAMES(l));
		
		for i = 1:PREFIX_COUNT
			for j = 1:TEST_COUNT
				for k = 1:SUFFIX_COUNT
					if ~PLOT_RAW_SUFFIXES(k)
						continue;
					end
					
					% Extract time and voltage data
					[time, voltage] = data{l, i, j, k}{1:2};
					
					% Sampling frequency, assuming equidistant time points
					Fs = 1 / mean(diff(time));
					
					subplot(SUFFIX_COUNT, TEST_COUNT, (TEST_COUNT*(k-1) + (j)));
					plot(time * 1000, voltage * VOLTAGE_SCALE, 'DisplayName', strcat("lights ", FILE_PREFIXES(i)));
					hold on;
					
					clear time voltage;
					
					xlabel('Time (ms)');
					ylabel('Voltage (V)');
					ylim([0, VOLTAGE_UPPER_VIEW_LIMIT(l)]);
					title(strcat(SENSOR_DIR_NAMES(l), " ", FILE_NAMES(j), " @", num2str(Fs), "Hz"));
					
					clear Fs;
					
					legend('Location', 'northwest');
				end
			end
		end
		
		hold off;
	end
end

%% Calculate FFT

if PLOT_FFT
	for l = 1:SENSOR_COUNT
		figure('Name', strcat(SENSOR_DIR_NAMES(l), " FFT"));
		
		for i = 1:PREFIX_COUNT
			for j = 1:TEST_COUNT
				for k = 1:SUFFIX_COUNT
					if ~PLOT_FFT_SUFFIXES(k)
						continue;
					end
					
					% Extract time and voltage data
					[time, voltage] = data{l, i, j, k}{1:2};
					
					L = length(voltage);
					
					% Sampling frequency, assuming equidistant time points
					Fs = 1 / mean(diff(time));
					f = Fs*(0:(L/2))/L;
					
					% Compute the FFT
					FFT = fft(voltage);
					FFT = abs(FFT ./ L);
					
					clear time voltage;
					
					% Compute the one-sided amplitude spectrum
					one_sided_spectrum = FFT(1:L/2+1);
					one_sided_spectrum(2:end-1) = 2 .* one_sided_spectrum(2:end-1);
					
					clear FFT L;
					
					if (FFT_DISCARD_HIGH_FREQUENCY)
						max_index = find( f > (4 * FFT_UPPER_VIEW_LIMIT ), 1 );
						
						f = f(1:max_index);
						one_sided_spectrum = one_sided_spectrum(1:max_index);
						
						clear max_index;
					end
					
					% Convert to dBV
					one_sided_spectrum = mag2db(one_sided_spectrum);
					
					% Plot the amplitude spectrum
					subplot(SUFFIX_COUNT, TEST_COUNT, (TEST_COUNT*(k-1) + (j)));
					plot(f, one_sided_spectrum, 'DisplayName', strcat("lights ", FILE_PREFIXES(i)), 'LineWidth', ((PREFIX_COUNT - (i - 1)) / 2));
					hold on;
					
					clear f one_sided_spectrum;
					
					xlabel('Frequency (Hz)');
					xlim([0, FFT_UPPER_VIEW_LIMIT]);
					ylabel('Amplitude (dBV)');
					title(strcat(SENSOR_DIR_NAMES(l), " FFT: ", FILE_NAMES(j), " @", "", num2str(Fs), "Hz"));
					
					clear Fs;
					
					legend('Location', 'northwest');
				end
				
				%{
 			subplot((SUFFIX_COUNT + 1), TEST_COUNT, (3*(SUFFIX_COUNT) + (j)));
			plot(data{l, i, j, (SUFFIX_COUNT + 1)}{1, 1}, data{l, i, j, (SUFFIX_COUNT + 1)}{1, 2});
			xlabel('Frequency (Hz)');
			xlim([0, FFT_UPPER_VIEW_LIMIT]);
			ylabel('Amplitude (dBV)');
			title(strcat(SENSOR_DIR_NAMES(l), " (lights ", FILE_PREFIXES(i), ") FFT: ", FILE_NAMES(j), " @", "Oscilloscope FFT"));
				%}
			end
		end
		
		hold off;
	end
end

clear data;