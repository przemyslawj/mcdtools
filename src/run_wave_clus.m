mcd_dir = '/local/data/public/pmj30/mecp2/2016-02';

setup_matlab;

mcd_files = listfiles(mcd_dir, '*.mcd');

spikeparam.stdmin = 5;
spikeparam.stdmax = 50;
spikeparam.detect_fmin = 100;
spikeparam.detect_order = 4;
spikeparam.sort_fmin = 100;
spikeparam.sort_order = 4;

clusparam.min_clus = 50;
clusparam.max_spk = 5000;
clusparam.maxtemp = 0.25;
for i = 1:length(mcd_files)
    file = mcd_files{i};
    [pathstr, name, ext] = fileparts(file);
    sprintf('Parsing file %s', file)
    output_dir = ['wave_clus/' name];
    %mcd2mat(file, output_dir);

    cd(output_dir);

    sprintf('Getting spikes')
    Get_spikes(listfiles('.', '*.mat'), 'parallel', true, 'par', spikeparam);

    sprintf('Clustering spikes')
    Do_clustering(listfiles('.', '*spikes.mat'), 'parallel', true, 'make_plots', false, 'par', clusparam);

    cd('../..');
end


