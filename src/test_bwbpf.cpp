#include <stdio.h>
#include <vector>
#include <math.h>

#include "bwbpf.h"

using namespace std;

int main() {
    int n = 100;
    double fs = 25000;
    double f1 = 500;
    double f2 = 10;
    vector<double> x1;
    vector<double> x2;

    for (int i = 0; i < n; ++i) {
        x1.push_back(1000 * sin (((double) i) / f1 * 2 * M_PI));
        x2.push_back(1000 * sin (((double) i) / f2 * 2 * M_PI));
    }

    vector<double> sum_x;
    for (int i = 0; i < n; ++i) {
        sum_x.push_back(x1[i] + x2[i]);
    }

    printf("Before bandpass\n");
    for (int i = 0; i < n; ++i) {
        printf("%.3f ", sum_x[i]);
    }
    butterworh_bandpass_filter(sum_x, 4, fs, 100, 1000);

    printf("\nAfter bandpass\n");
    for (int i = 0; i < n; ++i) {
        printf("%.3f ", sum_x[i]);
    }

    printf("\nCorrect \n");
    for (int i = 0; i < n; ++i) {
        printf("%.3f ", x1[i]);
    }

}
