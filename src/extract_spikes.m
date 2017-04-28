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

writer = add_meta(writer, 'par_stdmin', par.stdmin);
writer = add_meta(writer, 'sample_rate', par.sr);
writer = add_meta(writer, 'type', parts{1});
writer = add_meta(writer, 'culture_date', [parts{2} '-' parts{3} '-' parts{4}]);
writer = add_meta(writer, 'mea_id', parts{5});
writer = add_meta(writer, 'embryo_id', sscanf(parts{5}, '%d'));
div = sscanf(parts{6}(4:5), '%d');
writer = add_meta(writer, 'div', div);
writer = add_channel_meta(writer, mcdfileinfo.channel_names);
write_meta(writer);

all_spikes = [];
spikeCounts = zeros(1,mcdfileinfo.channels_count);
thresholds = zeros(1,mcdfileinfo.channels_count);

for i=1:mcdfileinfo.channels_count

    x = read_channel(mcdfile, i);

    [~, threshold, spike_indecies] = amp_detect(x,par);
    thresholds(i) = threshold;
    spike_times_sec = spike_indecies / par.sr;

    spikeCounts(i) = length(spike_times_sec);
    all_spikes = cat(2, all_spikes, spike_times_sec);
end

write_spikes(writer, all_spikes, spikeCounts, thresholds);
end
