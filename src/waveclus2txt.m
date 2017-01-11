data_dir = '../wave_clus';
subdirs = listfiles(data_dir, '*DIV*', 0);
for i = 1:length(subdirs)
    
    channel_files = listfiles(subdirs{i}, 'times*.mat');
    output_file = [subdirs{i} '.txt'];
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
        sorted_cluster_class = sortrows(cluster_class, 1);
        times_cell = accumarray(1 + sorted_cluster_class(:,1), sorted_cluster_class(:,2), [], @(x){x});
        clusters = unique(sorted_cluster_class(:,1));
        
        for cluster_index = 1:length(times_cell)
            cluster_id = clusters(cluster_index);
            fprintf(fid, '\n');
            fprintf(fid, 't       \tSpikes 2 %s_%d \tUnit\n', channel_name, cluster_index);
            fprintf(fid, '[ms]    \t[<B5>V]      \t    \n');
            times = times_cell{cluster_index};
            
            fprintf(fid, '%s', strjoin(string(times), '   \t-10      \t0   \n'));
            fprintf(fid, '   \t-10      \t0   \n');
        end
    end
    fclose(fid);
end
