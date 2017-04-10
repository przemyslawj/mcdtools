#include <assert.h>
#include <stdio.h>
#include <vector>

#include "findspikes.h"

using namespace std;

void test_singlespike() {
    vector<double> data = {1.0, 2.0, -10.0, 1.0};
    vector<double> spike_times = findspikes(data, 2.0, 1.0, 0.0);

    assert(spike_times.size() == 1);
    assert(spike_times[0] == 1000);
}

void test_spike_before_refractory_period() {
    vector<double> data = {1.0, 2.0, -10.0, -5, -10, 1.0, 0.0, 3.0, 1.5, 3.0};
    vector<double> spike_times = findspikes(data, 1000.0, 1.0, 3.0);

    assert(spike_times.size() == 1);
    assert(spike_times[0] == 2);
}

void test_spike_is_peak() {
    vector<double> data = {1.0, 2.0, -8.0, -10.0, 1.0, 1.0, 0.1, 0.5};
    vector<double> spike_times = findspikes(data, 1000.0, 1.0, 0.0);

    assert(spike_times.size() == 1);
    assert(spike_times[0] == 3);
}

int main() {
    printf("Running findspikes tests\n");
    test_singlespike();
    test_spike_before_refractory_period();
    test_spike_is_peak();
    return 0;
}

