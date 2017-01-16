mcd_dir = '/media/przemek/Storage/neurodata/mea/Mecp2-Hannah/';

setup_matlab;

mcd_files = listfiles(mcd_dir, 'Mecp2*.mcd');

spikeparam.stdmin = 4;
clusparam.min_clus = 50;
clusparam.max_spk = 5000;
clusparam.maxtemp = 0.25;
for i = 1:length(mcd_files)
    file = mcd_files{i};
    [pathstr, name, ext] = fileparts(file);
    sprintf('Parsing file %s', file)
    output_dir = ['wave_clus/' name];
    mcd2mat(file, output_dir);

    cd(output_dir);

    sprintf('Getting spikes')
    Get_spikes(listfiles('.', '*.mat'), 'parallel', true, 'par', spikeparam);

    sprintf('Clustering spikes')
    Do_clustering(listfiles('.', '*spikes.mat'), 'parallel', true, 'make_plots', false, 'par', clusparam);

    cd('../..');
end


