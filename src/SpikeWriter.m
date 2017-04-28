classdef SpikeWriter

    properties
        output_file
        array = 'MCS_8x8_200um'
        spacing = 200;
       
    end

    methods

        function obj = SpikeWriter(output_file)
          if nargin < 0
             error('Value must be numeric')
          end
          obj.output_file = output_file;
        end
       
        function [x, y] = get_epos(obj, channel)       
            row = floor(channel / 10) - 1;
            col = mod(channel, 10) - 1;
            x = row * obj.spacing;
            y = col * obj.spacing;
        end
    end

    methods (Abstract)
        write_spikes(obj, spikes, sCount, thresholds)
    end

end

