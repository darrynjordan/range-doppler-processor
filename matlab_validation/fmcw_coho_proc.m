%% Processing settings

n_peek = 10;                        % number of profiles to view during processing
is_windowing = 0;                   % enable tapering
is_sub = 0;                         % enable coherent subtraction
is_g2_out = 0;                      % enable the output of g2 compatible data

%% Experiment parameters

c = 299792458;                      % speed of light
df = 32;                            % decimation factor
f_s = 125e6/df;                     % sampling frequency [Hz]
b = 100e6;                          % sweep bandwidth [Hz]

t_up = 327.68e-6;                   % upramp period [s]
t_down = 163.84e-6;                 % downramp period [s]              
t_ramp = t_up + t_down;             % total modulation period per ramp [s]

%% Extract raw data

f_in_id = fopen('/home/darryn/Dropbox/Datasets/Loop-Back/MiloSAR/01_30_08_51_08/ch1.bin');
raw_data = fread(f_in_id, Inf, 'int16');

% f_c = 1.00001e6;    
% ns_dataset = 1e6; 
% T_raw = linspace(0, (ns_dataset - 1)/f_s, ns_dataset);
% raw_data = sin(2*pi*f_c*T_raw);

%% Setup output file

if (is_g2_out)
    f_out_id = fopen('g2.bin','w');
end;

%% Plot Dechirped Signal

ns_preview = 65536;
t_preview = linspace(0, (ns_preview - 1)/f_s, ns_preview);   % time vector for preview [s]

figure(1); 
plot(raw_data(1 : ns_preview));  
title('Raw Beat Signal');
xlabel('Sample Number');
ylabel('Arbitrary Amplitude');

% user identifies correct location to begin signal chopping
pause;
ns_chop = 2.227e4;
raw_data = raw_data(ns_chop : length(raw_data)); 

% remove dc offset
offset = mean(raw_data);
raw_data = raw_data - offset;

%% Calculated parameters

ns_dataset = length(raw_data);              % number of recorded samples
ns_ramp = floor(f_s*t_ramp);
n_ramps = floor(ns_dataset/ns_ramp);        % number of ramps
ns_trim = floor(f_s*1.1*t_down);
ns_padded = ns_ramp - ns_trim;              % number of samples each ramp will be zero padded to.
ns_fft = 2^nextpow2(ns_padded);             % number of samples in FFT
ns_profile = ns_fft/2 + 1;                  % number of samples in a range profile    

r_unamb = c*t_ramp/2;                       % unambiguous range [m]
r_rec = (f_s/2)*(t_up/b)*(c/2);             % maximum recordable range [m]


%% Define vectors

% time verctors
T_raw = linspace(0, (ns_dataset - 1)/f_s, ns_dataset);   % time vector for entire dataset [s]
T_padded = linspace(0, (ns_padded - 1)/f_s, ns_padded);  % time vector for single ramp [s]

% frequency vectors
F_fft = linspace(0, f_s/2, ns_profile)*(1e-6);           % frequency vector for the spectrum of one ramp [MHz]

% range vectors
R_fft = linspace(0, r_rec, ns_profile);                  % range vector for single ramp [m]
      
%% Define image matrices

RTI = zeros(ns_profile, n_ramps);
profile = zeros(ns_profile, 1);
int_profile = zeros(ns_profile, 1);
%ref_profile = zeros(ns_profile, 1);

%% Per-pulse processing
for i = 1 : n_ramps
     
    start = floor(i*f_s*t_ramp);
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
    
    int_profile = int_profile + profile;
    
    if(is_sub)
        profile = profile - ref_profile;        
    end;    
    
    if(is_g2_out)
        for k = 1 : ns_profile
            fwrite(f_out_id, real(profile(k)), 'float', 'ieee-le');
            fwrite(f_out_id, imag(profile(k)), 'float', 'ieee-le');
        end;        
    end;
    
    RTI(:, i) = profile;
    
    if (i <= n_peek)          
        
        figure(2);
        
        subplot(1,2,1);
        plot(T_padded, real(beat));
        title('Time Domain');
        xlabel('Time [s]');
        ylabel('Amplitude');
        xlim([0 10e-6]);


        subplot(1,2,2);
        plot(F_fft, 10*log(abs(profile)));
        title('Freq Domain');
        xlabel('Frequency [MHz]');
        ylabel('Amplitude [dB]');
        %ylim([80 160]);  
        xlim([-0.1 (max(F_fft) + 0.1)]);
        
        pause;
    end;

end;

clear raw_data;

figure(3);
subplot(1, 2, 1);
imagesc(T_raw, R_fft, 10*log(abs(RTI)));
title('RTI');
ylabel('Frequency [MHz]');
xlabel('Slow Time [s]');  
%ylim([1.89 1.91]);
%caxis([-50 100]);
colorbar;

subplot(1, 2, 2);
imagesc(T_raw, R_fft, angle(RTI));
title('Phase');
ylabel('Frequency [MHz]');
xlabel('Slow Time [s]');  
%ylim([1.89 1.91]);
colorbar;

fclose(f_in_id);

if (is_g2_out)
    fclose(f_out_id);
end;


 

   