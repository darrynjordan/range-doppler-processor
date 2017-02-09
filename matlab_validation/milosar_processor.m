%% Processing settings

n_peek = 5;                         % number of profiles to view during processing
is_windowing = 1;                   % enable tapering
is_sub = 0;                         % enable coherent subtraction
n_ref = 10;                          % index of profile to use as a reference for subtraction
is_g2_out = 0;                      % enable the output of g2 compatible data

%% Experiment parameters

c = 299792458;                      % speed of light
dF = 32;                            % decimation factor
F_s = 125e6/dF;                     % sampling frequency [Hz]
B = 100e6;                          % sweep bandwidth [Hz]

FN = 671089;
T_up = 327.68e-6;                   % upramp period [s]
T_down = 163.84e-6;                 % downramp period [s]              
T_ramp = T_up + T_down;             % total modulation period per ramp [s]

%% Extract raw data

f_in_id = fopen('/home/darryn/Dropbox/Datasets/Loop-Back/MiloSAR/02_09_22_45_36/ch1.bin');
raw_data = fread(f_in_id, Inf, 'int16');

% F_c = 1.09301e6;    
% ns_dataset = 1e6; 
% t_raw = linspace(0, (ns_dataset - 1)/F_s, ns_dataset);
% raw_data = sin(2*pi*F_c*t_raw);

%% Setup output file

if (is_g2_out)
    f_out_id = fopen('g2.bin','w');
end;

%% Plot Dechirped Signal

ns_preview = 65536;
t_preview = linspace(0, (ns_preview - 1)/F_s, ns_preview);   % time vector for preview [s]

figure(1); 
plot(raw_data(1 : ns_preview));  
title('Raw Beat Signal');
xlabel('Sample Number');
ylabel('Arbitrary Amplitude');

% user identifies correct location to begin signal chopping
pause;
ns_chop = 1.875e4;%2.85e4;
raw_data = raw_data(ns_chop : length(raw_data)); 

% remove dc offset
offset = mean(raw_data);
raw_data = raw_data - offset;

%% Calculated parameters

ns_dataset = length(raw_data);              % number of recorded samples
ns_ramp = floor(F_s*T_ramp);
n_ramps = floor(ns_dataset/ns_ramp);        % number of ramps
ns_fft = 2^nextpow2(ns_ramp);             % number of samples in FFT
ns_profile = ns_fft/2 + 1;                  % number of samples in a range profile    
ns_useful = ns_ramp - floor(F_s*T_up); 

R_max = 1000;
T_prop_max = (2*R_max)/c;
ns_prop_max = floor(F_s*T_prop_max);

%% Define vectors

% time verctors
t_raw = linspace(0, (ns_dataset - 1)/F_s, ns_dataset);   % time vector for entire dataset [s]
t_useful = linspace(0, (ns_useful - 1)/F_s, ns_useful);

% frequency vectors
f_profile = linspace(0, F_s/2, ns_profile)*(1e-6);           % frequency vector for the spectrum of one ramp [MHz]

% range vectors
%r_fft = linspace(0, R_rec, ns_profile);                  % range vector for single ramp [m]
      
%% Define image matrices

RTI = zeros(ns_profile, n_ramps);
profile = zeros(ns_profile, 1);
int_profile = zeros(ns_profile, 1);
ref_profile = zeros(ns_profile, 1);

%% Per-pulse processing
for i = 1 : n_ramps
     
    start = floor((i-1)*F_s*T_ramp) + 1 + ns_prop_max;
    stop  = start + ns_useful - 1;       
    
    if(stop > ns_dataset)
        continue;
    end;
    
    beat = raw_data(start : stop);    
    
    if(is_windowing)
        beat = beat.*hamming(ns_useful);
    end;
    
    beat_fft = fft(beat, ns_fft); 
    profile = beat_fft(1 : ns_profile);
    
    correction = exp(-1i*(2*pi)*((i)*T_ramp*get_vco(FN)));
    profile = profile.*correction;
    
    int_profile = int_profile + profile;
    
    if(is_sub)
%        if(i == n_ref)
%            ref_profile = profile;
%       end;
        
        profile = profile - ref_profile;  
        ref_profile = profile;
        
    end;    
    
    int_profile = int_profile + profile;
    
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
        plot(t_useful, real(beat));
        title('Time Domain');
        xlabel('Time [s]');
        ylabel('Amplitude');
        %xlim([0 10e-6]);


        subplot(1,2,2);
        plot(f_profile, 10*log(abs(int_profile)));
        title('Freq Domain');
        xlabel('Frequency [MHz]');
        ylabel('Amplitude [dB]');
        %ylim([50 180]);  
        xlim([-0.1 (max(f_profile) + 0.1)]);
        
        pause;
    end;

end;

clear raw_data;

figure(3);
subplot(1, 2, 1);
imagesc(t_raw, f_profile, 10*log(abs(RTI)));
title('RTI');
ylabel('Frequency [MHz]');
xlabel('Slow Time [s]');  
%ylim([0.9 1.1]);
%caxis([-50 100]);
colorbar;

subplot(1, 2, 2);
imagesc(t_raw, f_profile, angle(RTI));
title('Phase');
ylabel('Frequency [MHz]');
xlabel('Slow Time [s]');  
%ylim([0.9 1.1]);
colorbar;

fclose(f_in_id);

if (is_g2_out)
    fclose(f_out_id);
end;



 

   
