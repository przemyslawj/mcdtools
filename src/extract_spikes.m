function extract_spikes(mcdfile, output_file)

mcdfileinfo = mcd_fileinfo(mcdfile);
fid = fopen(output_file, 'w+');
if fid < 0
    error(['Couldnt open file ' output_file ' for writing']);
end

par = set_parameters();
par.sr = mcdfileinfo.sample_rate;
par.detect_fmin = 300;
par.detect_fmax = 6000;
par.w_pre = 1;
par.w_post = 1;
par.detection = 'neg';
par.ref = ceil(par.ref_ms/1000 * par.sr);

for i=1:mcdfileinfo.channels_count
    channel_name = mcdfileinfo.channel_names{i};
    fprintf(fid, '\nt       \tSpikes 2 %s \tUnit\n', channel_name);
    
    x = read_channel(mcdfile, i);

    [~, ~, spike_indecies] = amp_detect(x,par);
    spike_times_ms = spike_indecies / par.sr * 1000;
    
    for j=1:size(spike_times_ms, 2)
        fprintf(fid, '%d   \t-10      \t0   \n', spike_times_ms(j));
    end
end

fclose(fid);
end
