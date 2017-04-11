#include <numeric>
#include <vector>

#include <math.h>

#include "findspikes.h"

using namespace std;

double mean(const vector<double> &data) {
    double sum = accumulate(data.begin(), data.end(), 0.0);
    return sum / data.size();
}

double stddev(const vector<double> &data, double data_mean) {
    double mean_sq = data_mean * data_mean;
    double sq_sum = 0.0;
    for (unsigned int i = 0; i < data.size(); ++i) {
        double diff = data[i] - mean_sq;
        sq_sum += diff * diff / data.size();
    }
    return sqrt(sq_sum);
}

bool isnegativepeak(const vector<double> &data, unsigned int i) {
    return (i == (data.size() - 1)) || (data[i+1] > data[i]);
}

/**
 * Return spike times in seconds
 */
vector<double> findspikes(
        const vector<double> &data,
        int sampleRate,
        double stdthreshold,
        double spikeRefractoryPeriodMs) {

    double data_mean = mean(data);
    double data_stddev = stddev(data, data_mean);

    // use negative threshold
    double threshold = data_mean - stdthreshold * data_stddev;

    vector<double> spiketimes;
    double frameLengthMs = 1000.0 / sampleRate;
    double previousSpikeTime = -spikeRefractoryPeriodMs;

    for (unsigned int i = 0; i < data.size(); ++i) {
        if (data[i] < threshold && isnegativepeak(data, i)) {
            double spiketime = i * frameLengthMs;
            if (previousSpikeTime + spikeRefractoryPeriodMs <= spiketime) {
                spiketimes.push_back(spiketime);
                previousSpikeTime = spiketime;
            }
        }
    }

    return spiketimes;
}


