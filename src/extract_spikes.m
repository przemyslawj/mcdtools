function extract_spikes(mcdfile, output_file)

mcdfileinfo = mcd_fileinfo(mcdfile);
writer = H5SpikeWriter(output_file);

par = set_parameters();
par.sr = mcdfileinfo.sample_rate;
par.stdmin = 4;
par.detect_fmin = 300;
par.detect_fmax = 6000;
par.w_pre = 1;
par.w_post = 1;
par.detection = 'neg';
par.ref = ceil(par.ref_ms/1000 * par.sr);

[~, filename] = fileparts(mcdfile);
parts =  strsplit(filename, '[\\_-]', 'DelimiterType','RegularExpression');

add_meta(writer, 'par_stdmin', par.stdmin);
add_meta(writer, 'sample_rate', par.sr);
add_meta(writer, 'type', parts{1});
add_meta(writer, 'culture_date', [parts{2} '-' parts{3} '-' parts{4}]);
add_meta(writer, 'mea_id', parts{5});
add_meta(writer, 'embryo_id', sscanf(parts{5}, '%d'));
div = sscanf(parts{6}(4:5), '%d');
add_meta(writer, 'div', div);
write_meta(writer, mcdfileinfo.channel_names);
close(writer);

all_spikes = [];
spikeCounts = zeros(1,mcdfileinfo.channels_count);

for i=1:mcdfileinfo.channels_count

    x = read_channel(mcdfile, i);

    [~, ~, spike_indecies] = amp_detect(x,par);
    spike_times_sec = spike_indecies / par.sr;

    spikeCounts(i) = length(spike_times_sec);
    all_spikes = cat(2, all_spikes, spike_times_sec);
end

write_spikes(writer, all_spikes, spikeCounts);
end
