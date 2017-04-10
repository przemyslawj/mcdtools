#include "stdio.h"
#include "stdlib.h"

#include "bwbpf.h"
#include "mcdio.h"
#include "findspikes.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Arguments: filepath.mcd");
        return 1;
    }
    char* filepath = argv[1];
    CMCSAStreamFile m_MCSFile;
    short sFileOpenResult = m_MCSFile.OpenFile(filepath);
    string streamId = "elec0001";
    long streamIndex = m_MCSFile.GetStreamIndexForStreamID((char*) streamId.c_str());
    CMCSAStream* Stream = m_MCSFile.GetStream(streamIndex);
    long size = Stream->GetRawDataBufferSizeOfChannel();
    long sampleRate = Stream->GetSampleRate();

    int channelsInStream = Stream->GetChannelCount();
    double* data = (double *) malloc(sizeof(double) * size);
    short *buffer = (short *) malloc(sizeof(short) * size);
    for (int channel = 0; channel < channelsInStream; ++channel) {
        printf("Reading data of %ld bytes from channel %d\n", size, channel);
        ReadRawData(Stream, channel, size, buffer, data);
        vector<double> v(data, data + size);
        butterworh_bandpass_filter(v, 4, sampleRate, 300, 6000);
        vector<double> spiketimes = findspikes(v, sampleRate, 4.0, 2.0);

        printf("Spike times [ms] channel %d\n", channel);
        for (unsigned int i = 0; i < spiketimes.size(); ++i) {
            printf("%.2f\n", spiketimes[i]);
        }
    }

    free(buffer);
    free(data);
    return 0;
}

