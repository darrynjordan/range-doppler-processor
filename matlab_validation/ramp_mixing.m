%% Simulation parameters               
F_c = 0;                   
F_o = 200;                                                                       
B = 5;  

T_prop = 0;
T_up = 5;
T_down = 5;
T_ramp = T_up + T_down;
K = B/T_ramp;

Fs = 10*(F_c + B + F_o);                               

n_ramps = 2;
ns_ramp = floor(Fs*T_ramp); 
ns_up = floor(Fs*T_up);
ns_down = ns_ramp - ns_up;
ns_prop = floor(Fs*T_prop);

ns_fft = 2^nextpow2(ns_ramp);
ns_dataset = ns_ramp*n_ramps;
ns_profile = ns_fft/2 + 1;

RTI = zeros(ns_profile, n_ramps - 1);

t_raw  = linspace(0, (ns_dataset - 1)/Fs, ns_dataset);
t_up   = linspace(0, (ns_up -1)/Fs, ns_up);
t_down = linspace((-ns_down)/Fs, 0, ns_down);

t_beat = linspace(0, (ns_ramp - 1)/Fs, ns_ramp);
f_fft  = linspace(0, Fs/2, ns_profile); 

synth_1_up_phase = 0;
synth_2_up_phase = 0;
synth_1_down_phase = 0;
synth_2_down_phase = 0;
synth_1 = 0;
synth_2 = 0;

for i = 1 : n_ramps
    
    synth_1_up = exp(2*pi*1i*(F_c*t_up + K/2*t_up.^2) + 1i*synth_1_up_phase);
    synth_2_up = exp(2*pi*1i*((F_c + F_o)*t_up + K/2*t_up.^2) + 1i*synth_2_up_phase);
    
    synth_1_down_phase = 2*i*angle(exp(2*pi*1i*(F_c*i*(ns_up/Fs) + K/2*(ns_up/Fs).^2)));
    synth_2_down_phase = 2*i*angle(exp(2*pi*1i*((F_c + F_o)*i*(ns_up/Fs) + K/2*(ns_up/Fs).^2)));

    synth_1_down = exp(2*pi*1i*(F_c*t_down - K/2*t_down.^2) + 1i*synth_1_down_phase); 
    synth_2_down = exp(2*pi*1i*((F_c + F_o)*t_down - K/2*t_down.^2) + 1i*synth_2_down_phase);
    
    synth_1_up_phase = (i+1)*angle(exp(2*pi*1i*(F_c*i*(ns_up/Fs) + K/2*(ns_up/Fs).^2)));
    synth_2_up_phase = (i+1)*angle(exp(2*pi*1i*((F_c + F_o)*i*(ns_up/Fs) + K/2*(ns_up/Fs).^2)));
    
    synth_1 = [synth_1 synth_1_up synth_1_down];    
    synth_2 = [synth_2 synth_2_up synth_2_down];
end;


synth_1 = [zeros(1, ns_prop) synth_1]; 
synth_2 = [synth_2 zeros(1, ns_prop)];

raw_data = conj(synth_1).*synth_2;

%% Per-pulse processing
for i = 1 : n_ramps
     
    start = floor(i*Fs*T_ramp);
    stop  = start + ns_ramp - 1;   
    
    if(stop > ns_dataset)
        continue;
    end;
    
    beat = raw_data(start : stop);          
  
    chop_fft = fft(beat, ns_fft); 
    chop_profile = chop_fft(1 : ns_profile);
    
    RTI(:, i) = chop_profile;        
        
    figure(2);

    subplot(1,2,1);
    plot(t_beat, real(beat));
    title('Time Domain');
    xlabel('Time [s]');
    ylabel('Amplitude');
    xlim([0 5]);


    subplot(1,2,2);
    plot(f_fft, log(abs(chop_profile)));
    title('Freq Domain');
    xlabel('Frequency [MHz]');
    ylabel('Amplitude [dB]');
    %ylim([80 160]);  
    xlim([-0.1 (max(f_fft) + 0.1)]);

    pause;


end;

synth_1_profile = fft(synth_1, ns_fft);
synth_1_profile = synth_1_profile(1 : ns_profile);

synth_2_profile = fft(synth_2, ns_fft);
synth_2_profile = synth_2_profile(1 : ns_profile);

beat_profile = fft(raw_data, ns_fft);
beat_profile = beat_profile(1 : ns_profile);

figure(1);   
subplot(3, 2, 1);
plot(real(synth_1));
title('Synth 1 - Time Domain');
xlabel('Time [s]');
ylabel('Amplitude');

subplot(3, 2, 2);
plot(f_fft, log(abs(synth_1_profile)));
title('Synth 1 - Freq Domain');
xlabel('Frequency [Hz]');
ylabel('Amplitude');

subplot(3, 2, 3);
plot(real(synth_2));
title('Synth 2 - Time Domain');
xlabel('Time [s]');
ylabel('Amplitude');

subplot(3, 2, 4);
plot(f_fft, log(abs(synth_2_profile)));
title('Synth 2 - Freq Domain');
xlabel('Frequency [Hz]');
ylabel('Amplitude');

subplot(3, 2, 5);
plot(real(raw_data));
title('Time Domain');
xlabel('Time [s]');
ylabel('Amplitude');

subplot(3, 2, 6);
plot(f_fft, log(abs(beat_profile)));
title('Freq Domain');
xlabel('Frequency [Hz]');
ylabel('Amplitude');

figure(3);
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



