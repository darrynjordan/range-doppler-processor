%% Processing settings

is_windowing = 0;                   % enable tapering
is_sub = 0;                         % enable coherent subtraction
n_peek = 10;                        % number of profiles to view during processing

%% Experiment parameters

c = 299792458;                      % speed of light
DF = 32;                            % decimation factor
Fs = 125e6/DF;                      % sampling frequency [Hz]
B = 150e6;                          % sweep bandwidth [Hz]

T_up = 2*491.52e-6;                 % upramp period [s]
T_down = 163.84e-6;                 % downramp period [s]              
T_ramp = T_up + T_down;             % total modulation period per ramp [s]

%% Extract raw data

fid = fopen('/home/darryn/Dropbox/Datasets/Loop-Back/MiloSAR/ch1.bin');
raw_data = fread(fid, Inf, 'int16');

% Fc = 1.00001e6;    
% ns_dataset = 1e6; 
% t_raw = linspace(0, (ns_dataset - 1)/Fs, ns_dataset);
% raw_data = sin(2*pi*Fc*t_raw);


%% Plot Dechirped Signal

ns_preview = 65536;
t_preview = linspace(0, (ns_preview - 1)/Fs, ns_preview);   % time vector for preview [s]

figure(1); 
plot(raw_data(1 : ns_preview));  
title('Raw Beat Signal');
xlabel('Sample Number');
ylabel('Arbitrary Amplitude');

% user identifies correct location to begin signal chopping
pause;
ns_chop = 2.403e4;
raw_data = raw_data(ns_chop : length(raw_data)); 

% remove dc offset
offset = mean(raw_data);
raw_data = raw_data - offset;

%% Calculated parameters

ns_dataset = length(raw_data);              % number of recorded samples
ns_ramp = floor(Fs*T_ramp);
n_ramps = floor(ns_dataset/ns_ramp);        % number of ramps
ns_trim = floor(Fs*1.1*T_down);
ns_padded = ns_ramp - ns_trim;              % number of samples each ramp will be zero padded to.
ns_fft = 2^nextpow2(ns_padded);             % number of samples in FFT
ns_profile = ns_fft/2 + 1;                  % number of samples in a range profile    

R_unamb = c*T_ramp/2;                       % unambiguous range [m]
R_rec = (Fs/2)*(T_up/B)*(c/2);              % maximum recordable range [m]


%% Define vectors

% time verctors
t_raw = linspace(0, (ns_dataset - 1)/Fs, ns_dataset);   % time vector for entire dataset [s]
t_padded = linspace(0, (ns_padded - 1)/Fs, ns_padded);  % time vector for single ramp [s]

% frequency vectors
f_fft = linspace(0, Fs/2, ns_profile)*(1e-6);           % frequency vector for the spectrum of one ramp [MHz]

% range vectors
r_fft = linspace(0, R_rec, ns_profile);                 % range vector for single ramp [m]
      
%% Define image matrices

RTI = zeros(ns_profile, n_ramps);
profile = zeros(ns_profile, 1);
sum_profile = zeros(ns_profile, 1);
%ref_profile = zeros(ns_profile, 1);

%% Per-pulse processing
for i = 1 : n_ramps
     
    start = floor(i*Fs*T_ramp);
    stop  = start + ns_padded - 1;   
    
    if(stop > ns_dataset)
        continue;
    end;
    
    beat = raw_data(start : stop);          
  
    if(is_windowing)
        beat = beat.*hamming(ns_padded);
    end;
    
    beat_fft = fft(beat, ns_fft); 
    profile = beat_fft(1 : ns_profile);
    sum_profile = sum_profile + profile;
    
    if(is_sub)
        profile = profile - ref_profile;        
    end;    
    
    RTI(:, i) = profile;
    
    if (i <= n_peek)          
        
        figure(2);
        
        subplot(1,2,1);
        plot(t_padded, beat);
        title('Time Domain');
        xlabel('Time [s]');
        ylabel('Amplitude');
        %xlim([0 10e-6]);


        subplot(1,2,2);
        plot(f_fft, 10*log(abs(profile)));
        title('Freq Domain');
        xlabel('Frequency [MHz]');
        ylabel('Amplitude [dB]');
        %ylim([80 160]);  
        xlim([-0.1 (max(f_fft) + 0.1)]);
        
        pause;
    end;

end;

clear raw_data;

figure(3);
subplot(1, 2, 1);
imagesc(t_raw, r_fft, 10*log(abs(RTI)));
title('RTI');
ylabel('Frequency [MHz]');
xlabel('Slow Time [s]');  
%ylim([1.89 1.91]);
%caxis([-50 100]);
colorbar;

subplot(1, 2, 2);
imagesc(t_raw, r_fft, angle(RTI));
title('Phase');
ylabel('Frequency [MHz]');
xlabel('Slow Time [s]');  
%ylim([1.89 1.91]);
colorbar;

 

   