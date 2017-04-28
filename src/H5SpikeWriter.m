classdef H5SpikeWriter < SpikeWriter
    %H5SPIKEWRITER HDF5 output writer
    %   Writes spikes along with metadata to HDF5 file. The output file contains
    %   following datasets:
    %   /array - string with MEA name, e.g. 'MCS_8x8_200um'
    %   /names - string array with names of the elecectrodes,
    %   /spikes - double array with spike times in seconds
    %   /sCount - counts of spikes per each electrode
    %   /meta/creation_date
    %   
    
    properties
        fid
        gid
        epos
    end
    
    methods
        
        function obj = H5SpikeWriter(output_file)
            obj@SpikeWriter(output_file);
            plist = 'H5P_DEFAULT';
            obj.fid = H5F.create(obj.output_file,'H5F_ACC_TRUNC',plist,plist);
            obj.gid = H5G.create(obj.fid,'meta',plist,plist,plist);
        end
        
        function obj = add_channel_meta(obj, channel_names)
            
            write_dataset(obj, obj.gid, 'creation_date', datestr(now));
            write_dataset(obj, obj.fid, 'array', obj.array);
            
            write_cell_array(obj, channel_names, '/names');
            
            obj.epos = zeros(length(channel_names),2);
            for i=1:length(channel_names)
                [x, y] = obj.get_epos(str2double(channel_names(i)));
                obj.epos(i,1) = x;
                obj.epos(i,2) = y;
            end            
            
        end
       
        function obj = add_meta(obj, key, value)
            write_dataset(obj, obj.gid, key, value);
        end
        
        function write_meta(obj)
            %Close file for writing, needs to be called before writing with 
            %High level HDF5 API
            H5G.close(obj.gid);
            H5F.close(obj.fid);
            
            h5create(obj.output_file, '/epos', size(obj.epos));
            h5write(obj.output_file, '/epos', obj.epos);
        end
        
        % spikes - list of concatanated spike times
        % sCount - list of counts of spikes on each channel
        function obj = write_spikes(obj, spikes, sCount, thresholds)
            h5create(obj.output_file, '/spikes', length(spikes));
            h5write(obj.output_file, '/spikes', spikes);
            
            h5create(obj.output_file, '/sCount', length(sCount));
            h5write(obj.output_file, '/sCount', sCount);
            
            if (~isempty(thresholds) > 0)
                h5create(obj.output_file, '/thresholds', length(thresholds));
                h5write(obj.output_file, '/thresholds', thresholds);
            end
            
        end
        
    end
    
    methods (Access = private)
                
        function write_dataset(~, loc_id, name, data) 
            space_id = H5S.create('H5S_SCALAR');
            if isfloat(data)
                datatype = H5T.copy('H5T_NATIVE_DOUBLE');
            elseif ischar(data)
                datatype = H5T.copy('H5T_C_S1');
                H5T.set_size(datatype,numel(data));
            else
                error(['unsupported type to store in dataset, class=' ...
                    class(data)])
            end
            
            plist = 'H5P_DEFAULT';
            dataset_id = H5D.create(loc_id,name,datatype,space_id,plist);
            H5D.write(dataset_id,datatype,'H5S_ALL','H5S_ALL',...
                plist,data);
            H5D.close(dataset_id)
            H5S.close(space_id)
        end
        
        function write_cell_array(obj, vals, location)

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
            dset = H5D.create(obj.fid,location,VLstr_type,dspace,plist);

            % Write data
            H5D.write(dset,VLstr_type,'H5S_ALL','H5S_ALL','H5P_DEFAULT',vals);

            % Close file & resources
            H5P.close(plist);
            H5T.close(VLstr_type);
            H5S.close(dspace);
            H5D.close(dset);
        end
    end
    
end

