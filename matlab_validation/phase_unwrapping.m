%% Simulation parameters
                                                       
LEN = 32768;
FRAC_NUM = 671089;
F_ref = 10.67; %getVco(FRAC_NUM);
T_ramp = 1; %LEN/(100e6);
phi = 0;

F_s = 200;   

n_ramps = 10;
ns_ramp = floor(F_s*T_ramp);
ns_fft = 2^nextpow2(ns_ramp);
ns_dataset = ns_ramp*n_ramps;
ns_profile = ns_fft/2 + 1;

RTI = zeros(ns_profile, n_ramps - 1);

t_raw  = linspace(0, (ns_dataset - 1)/F_s, ns_dataset);
t_beat = linspace(0, (ns_ramp - 1)/F_s, ns_ramp);
f_fft  = linspace(0, F_s/2, ns_profile); 

raw_data = exp(1i*2*pi*F_ref*t_raw + phi);

%% Per-pulse processing
for i = 1 : n_ramps
     
    start = floor(i*F_s*T_ramp);
    stop  = start + ns_ramp - 1;   
    
    if(stop > ns_dataset)
        continue;
    end;
    
    beat = raw_data(start : stop);    
    
    beat = beat.*exp(-1i*2*pi*F_ref*(i)*T_ramp);

    %beat = beat.*hamming(ns_ramp)';     
    
    chop_fft = fft(beat, ns_fft);     
    chop_profile = chop_fft(1 : ns_profile);
    
    RTI(:, i) = chop_profile;        
        
    figure(1);

    subplot(1,2,1);
    plot(t_beat, real(beat));
    title('Time Domain');
    xlabel('Time [s]');
    ylabel('Amplitude');
    xlim([0 0.001]);
    
    subplot(1,2,2);
    plot(f_fft, log(abs(chop_profile)));
    title('Freq Domain');
    xlabel('Frequency [MHz]');
    ylabel('Amplitude [dB]');
    %ylim([80 160]);  
    %xlim([-0.1 (max(f_fft) + 0.1)]);

    pause;

end;

figure(2);
subplot(1, 2, 1);
imagesc(t_raw, f_fft, 10*log(abs(RTI)));
title('RTI');
ylabel('Frequency [MHz]');
xlabel('Slow Time [s]');  
%ylim([1.89 1.91]);
%caxis([-50 100]);
colorbar;

subplot(1, 2, 2);
imagesc(t_raw, f_fft, angle(RTI));
title('Phase');
ylabel('Frequency [MHz]');
xlabel('Slow Time [s]');  
%ylim([1.89 1.91]);
colorbar;
