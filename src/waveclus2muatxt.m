data_dir = '../wave_clus';
subdirs = listfiles(data_dir, '*DIV*', 0);
for i = 1:length(subdirs)

    channel_files = listfiles(subdirs{i}, 'times*.mat');
    output_file = [subdirs{i} '_mua.txt'];
    if isempty(output_file)
        continue
    end

    sprintf('Processing dir %s and writing to %s', subdirs{i}, output_file);
    fid = fopen(output_file, 'wt');
    fprintf(fid, 'Exported from WaveClus\n');
    for j = 1:length(channel_files)
        channel_file = channel_files{j};
        channel_name_start = regexp(channel_file, '\d\d.mat');
        channel_name = channel_file(channel_name_start:channel_name_start + 1);

        load(channel_file);
        spike_times = cluster_class(:,2);

        fprintf(fid, '\n');
        fprintf(fid, 't       \tSpikes 2 %s \tUnit\n', channel_name);
        fprintf(fid, '[ms]    \t[<B5>V]      \t    \n');
        times_str = strtrim(cellstr(num2str(spike_times)));
        fprintf(fid, strjoin(times_str, '   \t-10      \t0   \n'));
        fprintf(fid, '   \t-10      \t0   \n');
    end
    fclose(fid);
end
