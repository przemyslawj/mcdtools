classdef H5SpikeWriter < SpikeWriter
    %H5SPIKEWRITER Summary of this class goes here
    %   Detailed explanation goes here
    
    properties
    end
    
    methods
        
        function obj = H5SpikeWriter(output_file)
            obj@SpikeWriter(output_file);
                        
            h5create(obj.output_file, '/epos', size(obj.epos));
            h5write(obj.output_file, '/epos', obj.epos);
        end
        
        function write_meta(obj, channel_names)
            h5writeatt(obj.output_file, '/', '/meta/creation_date', datestr(now));
            h5writeatt(obj.output_file, '/', '/array', obj.array);
            
            write_cell_array(obj, channel_names, '/names');
        end
        
        function add_meta(obj, key, value)
            h5writeatt(obj.output_file, '/', ['/meta/' key], value);
        end
        
        % spikes - list of concatanated spike times
        % sCount - list of counts of spikes on each channel
        function write_spikes(obj, spikes, sCount)
            h5create(obj.output_file, '/spikes', length(spikes));
            h5write(obj.output_file, '/spikes', spikes);
            
            h5create(obj.output_file, '/sCount', length(sCount));
            h5write(obj.output_file, '/sCount', sCount);
        end
        
    end
    
    methods (Access = private)
        
        function write_cell_array(obj, vals, location)
            plist = 'H5P_DEFAULT';
            fid = H5F.open(obj.output_file,'H5F_ACC_RDWR',plist);

            % Set variable length string type
            VLstr_type = H5T.copy('H5T_C_S1');
            H5T.set_size(VLstr_type,'H5T_VARIABLE');

            % Create a dataspace for cellstr
            H5S_UNLIMITED = H5ML.get_constant_value('H5S_UNLIMITED');
            dspace = H5S.create_simple(1,numel(vals),H5S_UNLIMITED);

            % Create a dataset plist for chunking
            plist = H5P.create('H5P_DATASET_CREATE');
            H5P.set_chunk(plist,2); % 2 strings per chunk                             

            % Create dataset
            dset = H5D.create(fid,location,VLstr_type,dspace,plist);

            % Write data
            H5D.write(dset,VLstr_type,'H5S_ALL','H5S_ALL','H5P_DEFAULT',vals);

            % Close file & resources
            H5P.close(plist);
            H5T.close(VLstr_type);
            H5S.close(dspace);
            H5D.close(dset);
            H5F.close(fid);
        end
    end
    
end

