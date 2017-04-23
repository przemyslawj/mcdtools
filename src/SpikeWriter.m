classdef SpikeWriter
    %SPIKE_WRITER Summary of this class goes here
    %   Detailed explanation goes here

    properties
        output_file
        array = 'MCS_8x8_200um'
        epos = [
            200        1400;
            200        1200;
            200         600;
            200         400;
            400        1600;
            400        1200;
            400        1000;
            400         800;
            400         600;
            400         400;
            400         200;
            600        1400;
            600        1000;
            600         800;
            600         600;
            600         400;
            600         200;
            800        1400;
            800         800;
            800         400;
           1000        1600;
           1000        1200;
           1000        1000;
           1000         800;
           1000         600;
           1000         400;
           1000         200;
           1200        1600;
           1200        1000;
           1200         800;
           1200         600;
           1200         400;
           1200         200;
           1400        1400;
           1400        1200;
           1400         800;
           1400         600;
           1400         400;
           1400         200;
           1600        1000;
           1600         800
        ]
    end

    methods

        function obj = SpikeWriter(output_file)
          if nargin < 0
             error('Value must be numeric')
          end
          obj.output_file = output_file;
       end
    end

    methods (Abstract)
        write_spikes(obj, spikes, sCount)
    end

end

