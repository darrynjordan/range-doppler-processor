% Modified version of the matlab parser avialable from UM7 website
% Adapted to parse full binary file

%% Open the imu file.
fid = fopen('imu.bin');
imu_data = fread(fid, Inf, 'uint8');
ns_dataset = length(imu_data);

n_good_check = 0;
n_bad_check = 0;
n_iterations = 0;
n_registers = 0;

for index = 1 : ns_dataset   
    
    n_iterations = n_iterations + 1;
    
    if (index + 7 > ns_dataset)                  % not enough space left for the smallest full packet    
        break; 
    end;
    
    if((imu_data(index) == 's') && (imu_data(index + 1) == 'n') && (imu_data(index + 2) == 'p'))
    
        PT = imu_data(index + 3);    
        register_address = imu_data(index + 4);        
        
        % Check to see if this packet has data
        if bitand(PT, bitshift(1,7))
			% Packet has data.  Check to see if it is a batch operation
            if bitand(PT, bitshift(1,6))
				% Batch operation.
				n_registers = bitand(bitshift(PT,-2), 15); % Extract lower-order four bits
				ns_packet = 7 + n_registers*4;
            else
				% This packet has data, but it is not a batch operation. Packet size is 11.
				ns_packet = 11;
            end;
        else
			% This packet has no data. Packet size is 7
			ns_packet = 7;
        end;

        if (index + 5 + ns_packet > ns_dataset) % check if there is enough space left for data size
            continue;
        end;        
        
        computed_checksum = sum(uint16(imu_data(index:(index + ns_packet - 3))));
        received_checksum = typecast(flipud(uint8(imu_data((index + ns_packet - 2):(index + ns_packet - 1)))), 'uint16');
        
        data = zeros(ns_packet, 1);

        for k = 1 : ns_packet   
            data(k) = imu_data(index + 5 + k - 1);
        end;

        if(received_checksum == computed_checksum)   
            fprintf('start address \t= %i\n', register_address);
            fprintf('num registers \t= %i\n\n', n_registers);
            n_good_check = n_good_check + 1;
        else
            n_bad_check = n_bad_check + 1;
            fprintf('BAD CHECK\n');
        end;
    
    else
        continue;
    end;
    
end;

fclose(fid);

fprintf('%i/%i packets contained valid checksums (%f)\n', n_good_check, n_bad_check + n_good_check, (n_good_check/(n_bad_check + n_good_check)*100));

