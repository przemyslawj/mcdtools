#include <stdlib.h>

#include <cstring>
#include <memory>
#include <string>
#include <vector>


#include "typedefs.h"

#include "MCSAChannel.h"
#include "MCSAStream.h"
#include "MCSAStream.h"
#include "mat.h"
#include "mex.h"

using namespace std;

string getString(const mxArray *arg);
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]);
double* ReadRawData(CMCSAStream* Stream, int channelsInStream, long size);

string getString(const mxArray *arg) {
    size_t buflen = mxGetN(arg) + 1;
    char *buf = (char *) mxMalloc(buflen);
    mxGetString(arg, buf, (mwSize) buflen);
    return string(buf);
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
  CMCSAStreamFile m_MCSFile;
  if (nrhs != 2) {
      mexErrMsgIdAndTxt("mcdtools:mcdtools:nrhs", "Inputs: mcd_file channel_index");
  }
  if (nlhs > 1) {
      mexErrMsgIdAndTxt("mcdtools:mcdtools:nlhs", "Outputs: [x] stream of values");
  }

  string csFileName = getString(prhs[0]);
  int channel_index = (int) *((double *) mxGetPr(prhs[1]));

  short sFileOpenResult = m_MCSFile.OpenFile(csFileName.c_str());
  if(sFileOpenResult > 0) {
    string s = "Error loading file: " + csFileName + "\n\n";

    switch(sFileOpenResult) {
      case 1:
        s += "File can not be opened.";
        break;
      case 2:
        s += "Wrong file format.";
        break;
      case 3:
        s += "Wrong file header.";
	      break;
      case 4:
        s += "Empty data file.";
	      break;
      default:
	      break;
    }
    mexErrMsgIdAndTxt("mcdtools:mcdtools:nrhs", s.c_str());
  }

  string streamId = "elec0001";
  long streamIndex = m_MCSFile.GetStreamIndexForStreamID((char*) streamId.c_str());
  CMCSAStream* Stream = m_MCSFile.GetStream(streamIndex);

  if (channel_index < 0 || channel_index > Stream->GetChannelCount()) {
    mexErrMsgIdAndTxt("mcdtools:mcdtools:nrhs", "channel_index out of bounds");
  }

  long size = Stream->GetRawDataBufferSizeOfChannel();
  mxArray* pa = mxCreateDoubleMatrix(1, size, mxREAL);
  double* data = ReadRawData(Stream, channel_index, size);
  memcpy((void *)(mxGetPr(pa)), (void *)data, sizeof(double) * size);

  mxFree(data);
  m_MCSFile.CloseFile();

  plhs[0] = pa;
}


double* ReadRawData(CMCSAStream* Stream, int channel, long size) {

  int ADZero = Stream->GetADZero();
  double UnitsPerAD = Stream->GetUnitsPerAD();

  CMCSAChunk* currentChunk = Stream->GetFirstChunk();
  double* data = (double *) mxMalloc(sizeof(double) * size);
  short *buffer = (short *) mxMalloc(sizeof(short) * size);
  Stream->GetRawDataOfChannel(buffer, channel);
  for (int i = 0; i < size; ++i) {
    double realWordValue = (((unsigned short) buffer[i]) - ADZero) * UnitsPerAD;
    data[i] = realWordValue;
  }
  mxFree(buffer);
  return data;
}

