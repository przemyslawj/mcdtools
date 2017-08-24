Tools for Linux to read and detect spike times from Multielectrode Array data
in the MCD (Multi Channel Data) format.

# Dependencies
Dependencies for signal preprocessing and spike detection:

## Klusta
https://github.com/kwikteam/klusta/#quick-install-guide

## WaveClus
Download WaveClus
~~~~
wget https://github.com/csn-le/wave_clus/archive/testing.zip
unzip wave_clus-testing.zip
~~~~

# Build
~~~
make all
~~~

# Running spike detection with WaveClus
Instructions below assume the current directory is the root directory of the
project.

Run matlab with the MC library dependencies in the path.
~~~~
LD_LIBRARY_PATH="`pwd`/MC_StreamAnsiLib" LD_PRELOAD="/usr/lib/x86_64-linux-gnu/libstdc++.so.6" matlab

% Add Wave Clus to the path - update the path to your location
addpath(genpath([pwd '/wake_clus-testing']));
% Add the mcdtools code to the path
addpath(genpath([pwd '/src']));
addpath(genpath([pwd '/build']));
~~~~

Run spike detection which creates h5 files with the detected spikes and
metadata about the recording
~~~~
process_mcd_files('/path/to/input/mcd/files', 'output/dir/');
~~~~

