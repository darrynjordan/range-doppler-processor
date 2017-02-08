%% Simulation parameters
                                                       
LEN = 32768;
FRAC_NUM = 671089;
F_ref = 4.0625; %getVco(FRAC_NUM)*10^6;
T_ramp = 5; %LEN/(100e6);
PRF = 1/T_ramp;
phi = pi;

F_s = 20; %125e6/32;   

n_ramps = 100;
ns_ramp = floor(F_s*T_ramp);
ns_fft = 2^nextpow2(ns_ramp);
ns_dataset = ns_ramp*n_ramps;
ns_profile = ns_fft/2 + 1;

RTI = zeros(ns_profile, n_ramps - 1);

t_raw  = linspace(0, (ns_dataset - 1)/F_s, ns_dataset);
t_beat = linspace(0, (ns_ramp - 1)/F_s, ns_ramp);
f_profile = linspace(0, F_s/2, ns_profile); 

raw_data = exp(1i*2*pi*(3.4375)*t_raw + phi) +exp(1i*2*pi*(6.4062)*t_raw + phi) + exp(1i*2*pi*(8.4375)*t_raw + phi) + exp(1i*2*pi*(1.4062)*t_raw + phi);

%% Per-pulse processing
for i = 1 : n_ramps
     
    start = floor(i*F_s*T_ramp);
    stop  = start + ns_ramp - 1;   
    
    if(stop > ns_dataset)
        continue;
    end;
    
    correction = exp(-1i*(2*pi)*mod(i*T_ramp*(f_profile), 1)); 
    
%     figure(2);
%     plot(f_profile, angle(correction)); 
%     title('Phase vs Frequency over one PRF');
%     xlabel('Frequency');
%     ylabel('Phase');
%     xlim([0 PRF]);
%     ylim([-pi pi]);    
    
    beat = raw_data(start : stop);    
    
    %beat = beat.*hamming(ns_ramp)';     
    
    chop_fft = fft(beat, ns_fft);     
    
    chop_profile = chop_fft(1 : ns_profile);    
    
    chop_profile = chop_profile.*correction;
    
    RTI(:, i) = chop_profile;        
        
%     figure(3);
%     subplot(1,3,1);
%     plot(t_beat, real(beat));
%     title('Time Domain');
%     xlabel('Time [s]');
%     ylabel('Amplitude');
%     %xlim([0 0.1]);
%     
%     subplot(1,3,2);
%     plot(f_profile, log(abs(chop_profile)));
%     title('Freq Domain Mag');
%     xlabel('Frequency [MHz]');
%     ylabel('Amplitude [dB]');
%     %ylim([80 160]);  
%     %xlim([-0.1 (max(f_fft) + 0.1)]);
%     
%     subplot(1,3,3);
%     plot(f_profile, angle(chop_profile));
%     title('Freq Domain Phase');
%     xlabel('Frequency [MHz]');
%     ylabel('Phase');
%     %ylim([80 160]);  
%     %xlim([-0.1 (max(f_fft) + 0.1)]);
% 
%     pause;

end;

figure(3);
subplot(1, 2, 1);
imagesc(t_raw, f_profile, 10*log(abs(RTI)));
title('RTI');
ylabel('Frequency [MHz]');
xlabel('Slow Time [s]');  
%ylim([1.89 1.91]);
%caxis([-50 100]);
colorbar;

subplot(1, 2, 2);
imagesc(t_raw, f_profile, angle(RTI));
title('Phase');
ylabel('Frequency [MHz]');
xlabel('Slow Time [s]');  
%ylim([1.89 1.91]);
colorbar;
