function [result] = listfiles(src_dir, filenamepattern, recursive)
    if nargin < 3
        recursive = 1;
    end 
    
    matchingfiles = dir([src_dir '/' filenamepattern]);
    result = cell(1, length(matchingfiles));
    for index = 1:length(matchingfiles)
        result{index} = [src_dir '/' matchingfiles(index).name];
    end
    
    if recursive
        allfiles = dir(src_dir);
        for i = 1:length(allfiles)
            if (allfiles(i).isdir == 1) & (allfiles(i).name ~= '.' | allfiles(i).name ~= '..')
                result = [result listfiles([src_dir '/' allfiles(i).name], filenamepattern)];
            end
        end
    end
end

