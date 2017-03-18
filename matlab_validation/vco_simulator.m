F_c = 1000;
F_o = 1000.25139;
B = 300;

F_s = 5*(F_c);

n_ramps = 5;
SKEW = 0.8;
T_up = SKEW;
T_down = 1 - T_up;
T_ramp = 1;
T_prop = 0.293;
T_prop_max = 0.3;

ns_ramp = floor(F_s*T_ramp);
ns_fft = 2^nextpow2(ns_ramp);
ns_profile = ns_fft/2 + 1;
ns_dataset = ns_ramp*n_ramps;
ns_prop = floor(F_s*T_prop);
ns_prop_max = floor(F_s*T_prop_max);
ns_useful = ns_ramp - floor(F_s*T_up); 

RTI = zeros(ns_profile, n_ramps);

t_raw  = linspace(0, (ns_dataset - 1)/F_s, ns_dataset);
t_beat = linspace(0, (ns_ramp - 1)/F_s, ns_ramp);
t_useful = linspace(0, (ns_useful - 1)/F_s, ns_useful);
f_fft  = linspace(0, F_s/2, ns_profile); 

synth_1 = hilbert(vco(sawtooth(2*pi*t_raw, SKEW),[F_c               (F_c + B)], F_s));
synth_2 = hilbert(vco(sawtooth(2*pi*t_raw, SKEW),[(F_o + F_c) (F_o + F_c + B)], F_s));

target = synth_1.*exp(-1i*2*pi*F_c*T_prop); % phase proportional to propagation delay

synth_1 = [synth_1 zeros(1, ns_prop)]; 
synth_2 = [synth_2 zeros(1, ns_prop)];
target  = [zeros(1, ns_prop) target];

all_overlay = synth_1 + synth_2 + target;

raw_beat = conj(synth_1 + target).*synth_2;

figure(1);
subplot(1, 2, 1);
spectrogram(all_overlay, kaiser(256,5), 220, 512, F_s, 'yaxis');
title('Pre-Dechirp Spectrogram');
ylim([0 F_s/2000]);

subplot(1, 2, 2);
spectrogram(raw_beat, kaiser(256,5), 220, 512, F_s, 'yaxis');
title('Spectrogram of Beat Signal');
ylim([0 F_s/2000]);


%% Per-pulse processing
for i = 2 : n_ramps - 1
     
    start = floor((i-1)*F_s*T_ramp) + 1 + ns_prop_max;
    stop  = start + ns_useful - 1;
      
    if(stop > ns_dataset)
        continue;
    end;
    
    beat = raw_beat(start : stop);     
 
    chop_fft = fft(beat, ns_fft); 
    chop_profile = chop_fft(1 : ns_profile);   
  
    correction = exp(-1i*(2*pi)*((i)*T_ramp*(F_o))); 
    chop_profile = chop_profile.*correction;
  
    RTI(:, i) = chop_profile;        
        
%     figure(2); 
%     subplot(1,2,1);
%     plot(t_useful, real(beat));
%     title('Time Domain');
%     xlabel('Time [s]');
%     ylabel('Amplitude');
% 
%     subplot(1,2,2);
%     plot(f_fft, log(abs(chop_profile)));
%     title('Freq Domain');
%     xlabel('Frequency [MHz]');
%     ylabel('Amplitude [dB]');
%     %ylim([80 160]);  
%     xlim([-0.1 (max(f_fft) + 0.1)]);     
%     pause;
end;

% synth_1_profile = fft(synth_1, ns_fft);
% synth_1_profile = synth_1_profile(1 : ns_profile);
% 
% synth_2_profile = fft(synth_2, ns_fft);
% synth_2_profile = synth_2_profile(1 : ns_profile);
% 
% beat_profile = fft(raw_beat, ns_fft);
% beat_profile = beat_profile(1 : ns_profile);
% 
% figure(3);   
% subplot(3, 2, 1);
% plot(real(synth_1));
% title('Synth 1 - Time Domain');
% xlabel('Time [s]');
% ylabel('Amplitude');
% 
% subplot(3, 2, 2);
% plot(f_fft, log(abs(synth_1_profile)));
% title('Synth 1 - Freq Domain');
% xlabel('Frequency [Hz]');
% ylabel('Amplitude');
% 
% subplot(3, 2, 3);
% plot(real(synth_2));
% title('Synth 2 - Time Domain');
% xlabel('Time [s]');
% ylabel('Amplitude');
% 
% subplot(3, 2, 4);
% plot(f_fft, log(abs(synth_2_profile)));
% title('Synth 2 - Freq Domain');
% xlabel('Frequency [Hz]');
% ylabel('Amplitude');
% 
% subplot(3, 2, 5);
% plot(real(raw_beat));
% title('Time Domain');
% xlabel('Time [s]');
% ylabel('Amplitude');
% 
% subplot(3, 2, 6);
% plot(f_fft, log(abs(beat_profile)));
% title('Freq Domain');
% xlabel('Frequency [Hz]');
% ylabel('Amplitude');

figure(4);
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