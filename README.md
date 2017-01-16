# Dependencies

## SpikeOMatic
Seems to be not supported anymore
instructions: http://www.biomedicale.parisdescartes.fr/SpikeOMatic/SOM_Linux_Install.html

dependencies: biomedicale R packages
~~~~
source("https://bioconductor.org/biocLite.R")
biocLite()
biocLite(c('widgetTools', 'tkWidgets', 'DynDoc'))
~~~~

## Klusta
https://github.com/kwikteam/klusta/#quick-install-guide

## WaveClus
Download WaveClus
~~~~
wget https://github.com/csn-le/wave_clus/archive/testing.zip
unzip wave_clus-testing.zip
~~~~

run matlab and the code
~~~~
LD_LIBRARY_PATH="`pwd`/MC_StreamAnsiLib" LD_PRELOAD="/usr/lib/x86_64-linux-gnu/libstdc++.so.6" matlab

addpath(genpath([pwd '/wake_clus-testing']));
addpath(genpath([pwd '/src']));
run_wave_clus
~~~~

