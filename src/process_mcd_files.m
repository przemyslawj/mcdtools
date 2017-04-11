function process_mcd_files( input_dir, output_dir )

mcd_files = listfiles(input_dir, '*.mcd');

system(['mkdir -p ' output_dir]);
for i = 1:length(mcd_files)
    input_file = mcd_files{i};
    [~, filename] = fileparts(input_file);
    
    output_file = [ output_dir '/' filename '.txt'];
    ['Writing spikes to ' output_file]
    extract_spikes(input_file, output_file);
end

end

