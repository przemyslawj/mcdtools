#include "mcdio.h"


void ReadRawData(
        CMCSAStream* Stream,
        int channel,
        long size,
        short* buffer,
        double* output) {
  int ADZero = Stream->GetADZero();
  double UnitsPerAD = Stream->GetUnitsPerAD();

  Stream->GetRawDataOfChannel(buffer, channel);
  for (int i = 0; i < size; ++i) {
    double realWordValue = (((unsigned short) buffer[i]) - ADZero) * UnitsPerAD;
    output[i] = realWordValue;
  }
}

