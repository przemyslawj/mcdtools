#ifndef FIND_SPIKES_H
#define FIND_SPIKES_H

#include <vector>

/**
 * Return spike times
 */
std::vector<double> findspikes(
        std::vector<double> data,
        int sampleRate,
        double stdthreshold,
        double spikeRefractoryPeriodMs);

#endif

